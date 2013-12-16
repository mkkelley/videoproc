#pragma once

#include <opencv2/opencv.hpp>

namespace vp {
    cv::Mat analyzeFrame(const cv::Mat&);
    cv::Mat drawCircles(const cv::Mat&);
};
