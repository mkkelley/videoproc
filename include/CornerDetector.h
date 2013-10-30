#pragma once

#include <vector>
#include <opencv2/opencv.hpp>

class CornerDetector {
    public:
        std::vector<cv::KeyPoint> getKeyPoints(cv::Mat image) const;
        CornerDetector(std::string type = "");
    private:
        const std::string _defaultType = "PyramidGFTT";
        cv::Ptr<cv::FeatureDetector> _detector;
};
