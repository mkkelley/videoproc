#include "CornerDetector.h"

vector<KeyPoint> CornerDetector::getKeyPoints(Mat image) const {
    vector<KeyPoint> keyPoints;
    auto brisk = cv::BRISK();
    Mat descriptors;
    brisk(image, cv::noArray(), keyPoints, descriptors);
    return keyPoints;
}
