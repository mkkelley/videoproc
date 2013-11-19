#include "CameraUI.h"

#include "CornerDetector.h"
#include "Frame.h"

using cv::Mat;

CameraUI::CameraUI(QWidget* parent)
    : QWidget(parent),
    _cam(nullptr)
{
}

CameraUI::~CameraUI() {
    stopCamera();
}

void CameraUI::startCamera() {
    if (isCapturing()) {
        return;
    }
    _cam = new Camera(0);
    afterStart();
}

void CameraUI::stopCamera() {
    if (!isCapturing()) {
        return;
    }
    delete _cam;
    _cam = nullptr;
    afterStop();
}

Mat vp::analyzeFrame(Mat& inp) {
    static CornerDetector cd;
    Mat out;
    Frame f(inp);
    f.calculate(cd);
    cv::drawKeypoints(inp, f.getKeyPoints(), out);
    return out;
}
