#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

using cv::Mat;

class Camera {
    public:
        double getWidth();
        double getHeight();
        cv::Size getSize();
        double getFps();
        Mat getNextFrame();
        std::vector<Mat> captureVideo(int frames);
        Camera();

    private:
        cv::VideoCapture _cap;
        double _fps;
};
