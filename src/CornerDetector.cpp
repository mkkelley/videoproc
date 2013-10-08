#include "CornerDetector.h"

CornerDetector::CornerDetector(string type) {
    if (type == "") type = _defaultType;
    _detector = FeatureDetector::create(type);
}

vector<KeyPoint> CornerDetector::getKeyPoints(Mat image) const {
    vector<KeyPoint> keyPoints;
    _detector->detect(image, keyPoints);
    return keyPoints;
}
