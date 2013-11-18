#include "CameraUI.h"

CameraUI::CameraUI(QWidget* parent)
    : QWidget(parent),
    _cam(nullptr),
    _capturing(false)
{
}

CameraUI::~CameraUI() {
    stopCamera();
}

void CameraUI::startCamera() {
    if (_capturing) {
        return;
    }
    _cam = new Camera(0);
    _capturing = true;
    afterStart();
}

void CameraUI::stopCamera() {
    if (!_capturing) {
        return;
    }
    delete _cam;
    _cam = nullptr;
    _capturing = false;
    afterStop();
}
