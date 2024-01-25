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
    frame = cv::imdecode(cv::Mat(1, bytesRead, CV_8UC1, (void*)frameBuffer), cv::IMREAD_COLOR);

    if (!frame.empty()) {
        cv::imshow("Received Video", frame);
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

    // Main loop to receive and display video frames
    while (1) {
        char frameBuffer[FRAME_SIZE];
        int bytesRead = recvfrom(listenFd, frameBuffer, sizeof(frameBuffer), 0, (struct sockaddr *)&sin_client, &client_len);
       // printf("Bytes read %d\n",bytesRead);
        if (bytesRead < 0) {
            perror("Error receiving video frame");
            continue;
        }

        // Display the received video frame
        displayReceivedVideoFrame(frameBuffer, bytesRead);
    }

    // Close the socket (Note: This code doesn't reach here in the loop)
    close(listenFd);
    return 0;
}
