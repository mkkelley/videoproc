#pragma once

#include <functional>
#include <memory>

#include "Camera.h"
#include "View.h"

class CamFilter : public View {
    public:
        CamFilter(
                std::unique_ptr<View>,
                std::function<cv::Mat(cv::Mat&)>
                );
        double getWidth();
        double getHeight();
        cv::Size getSize();
        double getFps();
        cv::Mat getNextFrame();
        std::vector<cv::Mat> captureVideo(int frames);
        ~CamFilter() {}

    private:
        std::unique_ptr<View> _cam;
        std::function<cv::Mat(cv::Mat&)> _filter;
};
