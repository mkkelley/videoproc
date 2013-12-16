#include "CircleDetector.h"

using std::vector;
using cv::Mat;
using cv::Vec3f;

CircleDetector::CircleDetector() {

}

vector<Vec3f> CircleDetector::getCircles(Mat img) const {
    Mat blurred;
    img.copyTo(blurred);
    cv::GaussianBlur(img, blurred, cv::Size(9, 9), 2, 2);

    Mat cannyEdges;
    cv::Canny(blurred, cannyEdges, 80, 60);

    vector<vector<cv::Point>> contours;
    cv::findContours(cannyEdges, contours, cv::noArray(), CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

    vector<Vec3f> circles;
    for (vector<cv::Point> contour : contours) {
        cv::Point2f center;
        float radius;
        cv::minEnclosingCircle(contour, center, radius);
        if (radius < 10) continue;
        circles.push_back(Vec3f(center.x, center.y, radius));
    }
    return circles;
}
