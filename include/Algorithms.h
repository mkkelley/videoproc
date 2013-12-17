#pragma once

#include <opencv2/opencv.hpp>

namespace vp {
    cv::Mat analyzeFrame(const cv::Mat&);
    cv::Mat drawCircles(const cv::Mat&);
    cv::Mat drawEllipses(const cv::Mat&);
    cv::Mat drawContours(const cv::Mat&);
    cv::Mat drawMotion(const cv::Mat&);
    cv::Mat drawGhost(const cv::Mat&);
};
