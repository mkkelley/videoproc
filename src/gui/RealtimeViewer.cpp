#include "RealtimeViewer.h"

#include "MatView.h"

RealtimeViewer::RealtimeViewer()
    :_toggleButton(new QPushButton("Stop")),
    _layout(new QVBoxLayout()),
    _view(new MatView()),
    _cam(new Camera(0)),
    _capturing(true)
{
    auto f = _cam->getNextFrame();
    _view->setMat(f);
    _layout->addWidget(_view);
    _layout->addWidget(_toggleButton);
    setLayout(_layout);

    connect(_toggleButton, SIGNAL(released()), this, SLOT(handleToggleButton()));
}

void RealtimeViewer::handleToggleButton() {
    if (_capturing) {
        _toggleButton->setText("Start");
        stopCamera();
        return;
    }

    _toggleButton->setText("Stop");
    startCamera();
}

void RealtimeViewer::startCamera() {
    if (!_capturing) {
        _cam = new Camera(0);
        _capturing = true;
    }
}

void RealtimeViewer::stopCamera() {
    if (_capturing) {
        delete _cam;
        _capturing = false;
    }
}
