#include "CameraUI.h"

#include "CircleDetector.h"
#include "CornerDetector.h"
#include "Frame.h"

using cv::Mat;

CameraUI::CameraUI()
    : _cam(nullptr)
{
    afterStart([](){});
    afterStop([](){});
}

CameraUI::~CameraUI() {
    stopCamera();
}

void CameraUI::startCamera() {
    if (isCapturing()) {
        return;
    }
    _cam = new Camera(0);
    _afterStart();
}

void CameraUI::stopCamera() {
    if (!isCapturing()) {
        return;
    }
    delete _cam;
    _cam = nullptr;
    _afterStop();
}

cv::Size CameraUI::getSize() {
    return _cam->getSize();
}

double CameraUI::getFps() {
    return _cam->getFps();
}

cv::Mat CameraUI::getNextRawFrame() {
    return _cam->getNextRawFrame();
}

std::vector<cv::Mat> CameraUI::captureVideo(int frames) {
    return _cam->captureVideo(frames);
}

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
        cv::circle(out, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
    }
    return out;
}
