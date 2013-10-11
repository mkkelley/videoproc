#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

class View {
    public:
        virtual double getWidth() = 0;
        virtual double getHeight() = 0;
        virtual cv::Size getSize() = 0;
        virtual double getFps() = 0;
        virtual cv::Mat getNextFrame() = 0;
        virtual std::vector<cv::Mat> captureVideo(int frames) = 0;
        virtual ~View() {};
};
