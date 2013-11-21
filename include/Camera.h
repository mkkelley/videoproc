#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

#include "View.h"

class Camera : public View {
    public:
        double getWidth();
        double getHeight();
        cv::Size getSize() override;
        double getFps() override;
        cv::Mat getNextRawFrame() override;
        std::vector<cv::Mat> captureVideo(int frames) override;
        Camera();
        Camera(int which);
        virtual ~Camera() = default;

    protected:
        cv::VideoCapture _cap;
        double _fps;
};
