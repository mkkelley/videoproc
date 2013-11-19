#pragma once

#include <functional>
#include <vector>
#include <opencv2/opencv.hpp>

class View {
    public:
        virtual cv::Size getSize() = 0;
        virtual double getFps() = 0;
        virtual cv::Mat getNextRawFrame() = 0;
        virtual std::vector<cv::Mat> captureVideo(int frames) = 0;
        virtual ~View() {};

        cv::Mat getNextFrame();
        void addFilter(std::function<cv::Mat(cv::Mat&)>);
        void clearFilters();
    private:
        std::vector<std::function<cv::Mat(cv::Mat&)>> _filters;
};
