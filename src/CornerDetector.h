#pragma once

#include <vector>
#include <opencv2/opencv.hpp>

using std::vector;
using cv::KeyPoint;
using cv::Mat;

class CornerDetector {
    public:
        vector<KeyPoint> getKeyPoints(Mat image) const;
    private:
};
