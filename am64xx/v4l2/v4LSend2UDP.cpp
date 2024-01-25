#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#if 0
// #define PACKETSIZE 345600 // Adjust packet size as needed
#define NEW_WIDTH 320 // Adjust video resolution as needed
#define NEW_HEIGHT 240
//#define PACKETSIZE 1458
#define FPS 30           // Adjust frame rate as needed
#define PORT 2307        // Default port
#define FIXED_FRAME_SIZE 9884
#endif

#if 1
 #define PACKETSIZE 345600 // Adjust packet size as needed
#define NEW_WIDTH 1280 // Adjust video resolution as needed
#define NEW_HEIGHT 720
//#define PACKETSIZE 
#define FPS 30           // Adjust frame rate as needed
#define PORT 2307        // Default port
#define FIXED_FRAME_SIZE 60000
#endif


struct VideoBuffer {
    void* start;
    size_t length;
};

struct VideoBuffer* buffers = nullptr;
unsigned int bufferCount = 0;

void printSupportedFormats(int videoFd) {
    struct v4l2_fmtdesc fmtdesc;
    memset(&fmtdesc, 0, sizeof(struct v4l2_fmtdesc));
    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    printf("Supported video formats:\n");

    while (ioctl(videoFd, VIDIOC_ENUM_FMT, &fmtdesc) == 0) {
        printf("  %s\n", fmtdesc.description);
        fmtdesc.index++;
    }
}

void initializeV4L2(int* videoFd) {
    // Open the V4L2 device
    *videoFd = open("/dev/video0", O_RDWR);
    
    if (*videoFd == -1) {
        perror("Failed to open video device");
        exit(EXIT_FAILURE);
    }

    //printSupportedFormats(*videoFd);  

    // Set video format and resolution
    struct v4l2_format format;
    memset(&format, 0, sizeof(struct v4l2_format));
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.width = NEW_WIDTH;
    format.fmt.pix.height = NEW_HEIGHT;
    // // format.fmt.pix.pixelformat = V4L2_PIX_FMT_MPEG; // Adjust pixel format as needed

    // if(format.fmt.pix.pixelformat != V4L2_PIX_FMT_MPEG)
    // {
    //     perror("format Not accepted \n");
    //     exit(EXIT_FAILURE);
    // }

    if (ioctl(*videoFd, VIDIOC_S_FMT, &format) == -1) {
        perror("Failed to set video format");
        exit(EXIT_FAILURE);
    }

    // Request and initialize buffers
    struct v4l2_requestbuffers reqbufs;
    memset(&reqbufs, 0, sizeof(struct v4l2_requestbuffers));
    reqbufs.count = 4; // Adjust buffer count as needed
    reqbufs.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    reqbufs.memory = V4L2_MEMORY_MMAP;

    if (ioctl(*videoFd, VIDIOC_REQBUFS, &reqbufs) == -1) {
        perror("Failed to request video buffers");
        exit(EXIT_FAILURE);
    }

    buffers = (struct VideoBuffer*)malloc(reqbufs.count * sizeof(struct VideoBuffer));
    if (!buffers) {
        perror("Failed to allocate memory for video buffers");
        exit(EXIT_FAILURE);
    }

    bufferCount = reqbufs.count;

    //printSupportedFormats(*videoFd);

    for (unsigned int i = 0; i < reqbufs.count; i++) {
        struct v4l2_buffer buf;
        memset(&buf, 0, sizeof(struct v4l2_buffer));
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        if (ioctl(*videoFd, VIDIOC_QUERYBUF, &buf) == -1) {
            perror("Failed to query video buffer");
            exit(EXIT_FAILURE);
        }

        buffers[i].length = buf.length;
        buffers[i].start = mmap(NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, *videoFd, buf.m.offset);

        if (buffers[i].start == MAP_FAILED) {
            perror("Failed to map video buffer");
            exit(EXIT_FAILURE);
        }

        if (ioctl(*videoFd, VIDIOC_QBUF, &buf) == -1) {
            perror("Failed to enqueue video buffer");
            exit(EXIT_FAILURE);
        }
    }

    // Start video streaming
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(*videoFd, VIDIOC_STREAMON, &type) == -1) {
        perror("Failed to start video streaming");
        exit(EXIT_FAILURE);
    }
}

void cleanupBuffers(int videoFd) {
    for (unsigned int i = 0; i < bufferCount; i++) {
        if (buffers[i].start != MAP_FAILED) {
            munmap(buffers[i].start, buffers[i].length);
        }
    }
    free(buffers);

    // Stop video streaming
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(videoFd, VIDIOC_STREAMOFF, &type) == -1) {
        perror("Failed to stop video streaming");
    }
}

void captureAndSendFrame(int videoFd, int connection, struct sockaddr_in *sin_server) {
    struct v4l2_buffer buf;

    memset(&buf, 0, sizeof(struct v4l2_buffer));
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    if (ioctl(videoFd, VIDIOC_DQBUF, &buf) == -1) {
        perror("Failed to dequeue video buffer");
        return;
    }
    int packetSize = FIXED_FRAME_SIZE;

    int datasent = sendto(connection, buffers[buf.index].start, packetSize, 0, (struct sockaddr *)sin_server, sizeof(*sin_server));
    //printf("Data sent=%d\n",datasent);
   
    if (datasent < 0) {
        perror("Error sending packet over UDP");
    }

    if (ioctl(videoFd, VIDIOC_QBUF, &buf) == -1) {
        perror("Failed to enqueue video buffer");
    }
}

int main(int argc, char *argv[]) {
    int videoFd;
    int connection;
    struct sockaddr_in sin_server = {0};

    const char* ip = nullptr;
    int port = PORT; // Default port

    if (argc == 3) {
        ip = argv[1];
        port = atoi(argv[2]);
    } else if (argc != 2) {
        fprintf(stderr, "Usage: %s <server_ip> [<server_port>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Create a UDP socket
    connection = socket(AF_INET, SOCK_DGRAM, 0);
    if (connection == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address
    sin_server.sin_family = AF_INET;
    sin_server.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &sin_server.sin_addr) <= 0) {
        perror("Invalid server address");
        close(connection);
        exit(EXIT_FAILURE);
    }

    // Initialize V4L2 device and buffers
    initializeV4L2(&videoFd);

    printf("INFO: video started...\n");
    while (1) {
        captureAndSendFrame(videoFd, connection, &sin_server);
    }

    // Clean up and close resources
    cleanupBuffers(videoFd);
    close(connection);

    return 0;
}
