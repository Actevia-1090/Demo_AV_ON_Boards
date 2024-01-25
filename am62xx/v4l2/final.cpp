#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <opencv2/opencv.hpp>

#define LISTEN_PORT 2308
#define FRAME_SIZE  60000 // Adjust this based on your needs
//#define PACKETSIZE 1458

void displayReceivedVideoFrame(const char* frameBuffer, int bytesRead) {
    cv::Mat frame;
    /*

        cv::Mat(1, bytesRead, CV_8UC1, (void*)frameBuffer): 
        This part of the code creates a cv::Mat object, which is an OpenCV data structure used to store and manipulate images


        It's using CV_8UC1 as the type, which means it's an 8-bit unsigned single-channel matrix (commonly used for grayscale images).
    */

	printf ("before decode\n");
 //   frame = cv::imdecode(cv::Mat(1, 10, CV_8UC1, (void*)"0123456789"), cv::IMREAD_COLOR);
    frame = cv::imdecode(cv::Mat(1, bytesRead, CV_8UC1, (void*)frameBuffer), cv::IMREAD_COLOR);

    printf ("After Decode\n");
    if (!frame.empty()) {
	    printf ("INside Frame Display\n");
        cv::imshow("Received Video", frame);
	printf ("Before wait\n");
        cv::waitKey(1);
    }
}

int main() {
    // UDP socket setup to receive video frames
    int listenFd;
    struct sockaddr_in sin_listen = {0};
    struct sockaddr_in sin_client = {0};
    socklen_t client_len = sizeof(sin_client);

    listenFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (listenFd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sin_listen.sin_addr.s_addr = htonl(INADDR_ANY);
    sin_listen.sin_family = AF_INET;
    sin_listen.sin_port = htons(LISTEN_PORT);

    if (bind(listenFd, (struct sockaddr *)&sin_listen, sizeof(sin_listen)) == -1) {
        perror("Socket bind failed");
        exit(EXIT_FAILURE);
    }
//    return 0;
    // Main loop to receive and display video frames
    while (1) {
        char frameBuffer[FRAME_SIZE];
        int bytesRead = recvfrom(listenFd, frameBuffer, sizeof(frameBuffer), 0, (struct sockaddr *)&sin_client, &client_len);
        printf("Bytes read %d\n",bytesRead);
        if (bytesRead < 0) {
            perror("Error receiving video frame");
            continue;
        }

//	printf ();
        // Display the received video frame
        displayReceivedVideoFrame(frameBuffer, bytesRead);
        printf("Bytes read %d\n",bytesRead);
    }

    // Close the socket (Note: This code doesn't reach here in the loop)
    close(listenFd);
    return 0;
}
