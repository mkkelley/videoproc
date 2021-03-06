#include "CameraUI.h"

#include "Algorithms.h"

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
