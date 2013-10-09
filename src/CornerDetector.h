#pragma once

#include <vector>
#include <opencv2/opencv.hpp>

using std::string;
using std::vector;
using cv::FeatureDetector;
using cv::KeyPoint;
using cv::Mat;
using cv::Ptr;

class CornerDetector {
    public:
        vector<KeyPoint> getKeyPoints(Mat image) const;
        CornerDetector(string type = "");
    private:
        const std::string _defaultType = "PyramidGFTT";
        Ptr<FeatureDetector> _detector;
};
