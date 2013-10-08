#include "CornerDetector.h"

vector<KeyPoint> CornerDetector::getKeyPoints(Mat image) const {
    vector<KeyPoint> keyPoints;
    auto orb = cv::ORB();
    orb(image, cv::noArray(), keyPoints, cv::noArray());
    return keyPoints;
}
