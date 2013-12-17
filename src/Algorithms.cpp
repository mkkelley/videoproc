#include "Algorithms.h"

#include "CircleDetector.h"
#include "CornerDetector.h"
#include "Frame.h"

using std::vector;
using cv::Mat;

Mat vp::analyzeFrame(const Mat& inp) {
    static CornerDetector cd;
    Mat out;
    Frame f(inp);
    f.calculate(cd);
    cv::drawKeypoints(inp, f.getKeyPoints(), out);
    return out;
}

Mat vp::drawCircles(const Mat& inp) {
    static CircleDetector cd;
    Mat out = inp;
    std::vector<cv::Vec3f> circles = cd.getCircles(inp);
    for (cv::Vec3f circle : circles) {
        cv::Point center(circle[0], circle[1]);
        int radius = circle[2];
        cv::circle(out, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
        cv::circle(out, center, radius, cv::Scalar(0, 0, 255), 2, 8, 0);
    }
    return out;
}

Mat vp::drawEllipses(const Mat& inp) {
    static EllipseDetector ed;
    Mat out = inp;
    vector<cv::RotatedRect> ellipses = ed.getEllipses(inp);
    for (cv::RotatedRect r : ellipses) {
        cv::ellipse(out, r, cv::Scalar(0, 0, 255), 2);
    }
    return out;
}

Mat vp::drawContours(const Mat& inp) {
    Mat blurred;
    inp.copyTo(blurred);
    cv::GaussianBlur(inp, blurred, cv::Size(9, 9), 2, 2);

    Mat cannyEdges;
    cv::Canny(blurred, cannyEdges, 80, 60);

    vector<vector<cv::Point>> contours;
    cv::findContours(cannyEdges, contours, cv::noArray(), CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

    Mat out = inp;
    cv::drawContours(out, contours, -1, cv::Scalar(0, 255, 0));
    return out;
}
