#include "CornerDetector.h"

CornerDetector::CornerDetector(string type) {
    _detector = FeatureDetector::create(_defaultType);
}

vector<KeyPoint> CornerDetector::getKeyPoints(Mat image) const {
    vector<KeyPoint> keyPoints;
    _detector->detect(image, keyPoints);
    return keyPoints;
}
