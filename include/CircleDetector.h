#pragma once

#include <vector>
#include <opencv2/opencv.hpp>

class CircleDetector {
    public:
        CircleDetector();
        std::vector<cv::Vec3f> getCircles(cv::Mat image) const;
};
