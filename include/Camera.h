#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

#include "View.h"

class Camera : public View {
    public:
        double getWidth();
        double getHeight();
        cv::Size getSize();
        double getFps();
        cv::Mat getNextRawFrame();
        std::vector<cv::Mat> captureVideo(int frames);
        Camera();
        Camera(int which);
        virtual ~Camera();

    protected:
        cv::VideoCapture _cap;
        double _fps;
};
