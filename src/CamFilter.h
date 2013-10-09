#pragma once

#include <memory>

#include "Camera.h"

class CamFilter : public Viewer {
    public:
        CamFilter(
                std::unique_ptr<Viewer>,
                std::function<Mat(Mat&)>
                );
        double getWidth();
        double getHeight();
        cv::Size getSize();
        double getFps();
        cv::Mat getNextFrame();
        std::vector<cv::Mat> captureVideo(int frames);
        ~CamFilter() {}

    private:
        std::unique_ptr<Viewer> _cam;
        std::function<Mat(Mat&)> _filter;
};
