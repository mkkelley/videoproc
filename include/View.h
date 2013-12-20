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
        virtual ~View() = default;

        /**
         * Take the output of getNextRawFrame() and apply all filters to it,
         * returning the resulting image.
         */
        cv::Mat getNextFrame();

        /**
         * Add a filter to the output of getNextRawFrame(). Note that this is
         * not an exclusionary filter, but a video filter, modifying the input
         * and producing output. Applied in order of addition.  @param fn The
         * filter function.
         */
        void addFilter(std::function<cv::Mat(cv::Mat&)> fn);

        /**
         * Remove all previously-added filters.
         */
        void clearFilters();
    private:
        std::vector<std::function<cv::Mat(cv::Mat&)>> _filters;
};
