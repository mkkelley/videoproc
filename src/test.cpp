#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <memory>

#include "Camera.h"
#include "Recorder.h"

int main(int, char**) {
    Camera cam;
    double fps = cam.getFps();
    std::cout << "FPS: "  << fps << std::endl;

    cv::Size inputSize = cam.getSize();
    std::cout << "Input Resolution: " << inputSize << std::endl;

    Recorder r(&cam);
    r.record("output.avi", 100);
    return 0;
}
