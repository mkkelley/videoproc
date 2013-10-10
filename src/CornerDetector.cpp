#include "CornerDetector.h"

using std::string;
using std::vector;
using cv::FeatureDetector;
using cv::KeyPoint;
using cv::Mat;

CornerDetector::CornerDetector(string type) {
    if (type == "") type = _defaultType;
    _detector = FeatureDetector::create(type);
}

vector<KeyPoint> CornerDetector::getKeyPoints(Mat image) const {
    vector<KeyPoint> keyPoints;
    _detector->detect(image, keyPoints);
    return keyPoints;
}
