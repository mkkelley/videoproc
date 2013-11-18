#include "CameraUI.h"

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
