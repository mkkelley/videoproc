#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <memory>

using cv::Mat;

class Camera {
    public:
        double getWidth();
        double getHeight();
        cv::Size getSize();
        double getFps();
        std::vector<Mat> captureVideo(int frames);
        Camera();

    private:
        cv::VideoCapture _cap;
        double _fps;
};
