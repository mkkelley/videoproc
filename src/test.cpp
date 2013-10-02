#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>

using namespace cv;

double testFps(VideoCapture& cap) {
    if (!cap.isOpened()) {
        return -1;
    }

    time_t start, end;
    double fps;
    double sec;
    int counter = 0;
    time(&start);
    Mat image;
    while(counter < 120) {
        cap >> image;
        time(&end);
        ++counter;
    }
    sec = difftime(end, start);
    fps = counter / sec;
    return fps;
}

int main(int, char**) {
    VideoCapture cap(0);
    if (cap.isOpened()) {
        std::cout << "Opened camera.\n";
    } else {
        std::cout << "Couldn't open camera.\n";
        return -1;
    }

    double fps = testFps(cap);
    std::cout << "FPS: "  << fps << std::endl;

    Size inputSize = Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH),
                (int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    std::cout << "Input Resolution: " << inputSize << std::endl;

    VideoWriter outputVideo;
    outputVideo.open("output.avi", CV_FOURCC('X', 'V', 'I', 'D'), fps, inputSize, true);

    if (!outputVideo.isOpened()) {
        std::cout << "Problem. Couldn't open video output.";
    }

    Mat image;
    bool x = true;
    int n = 0;
    while (x && n < 100) {
        cap >> image;
        outputVideo << image;
        ++n;
    }
    return 0;
}
