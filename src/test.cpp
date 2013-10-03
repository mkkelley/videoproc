#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <memory>

#include "Camera.h"

int main(int, char**) {
    Camera cam;
    double fps = cam.getFps();
    std::cout << "FPS: "  << fps << std::endl;

    cv::Size inputSize = cam.getSize();
    std::cout << "Input Resolution: " << inputSize << std::endl;

    cv::VideoWriter outputVideo;
    outputVideo.open("output.avi", CV_FOURCC('M', 'J', 'P', 'G'), fps, inputSize, true);

    if (!outputVideo.isOpened()) {
        std::cout << "Problem. Couldn't open video output.";
        return -1;
    }

    std::vector<Mat> output = cam.captureVideo(100);

    for (size_t i = 0; i < 100; i++) {
        outputVideo << output[i];
    }

    return 0;
}
