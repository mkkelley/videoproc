#include "RealtimeViewer.h"

#include "MatView.h"

RealtimeViewer::RealtimeViewer()
    :_toggleButton(new QPushButton("Stop")),
    _layout(new QVBoxLayout()),
    _view(new MatView()),
    _capturing(false),
    _timer(new QTimer(this))
{
    _layout->addWidget(_view);
    _layout->addWidget(_toggleButton);
    setLayout(_layout);

    connect(_toggleButton, SIGNAL(released()), this, SLOT(handleToggleButton()));
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateDisplay()));
    startCamera();
}

void RealtimeViewer::updateDisplay() {
    if (!_capturing) {
        return;
    }
    cv::Mat f = _cam->getNextFrame();
    _view->setMat(f);
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
        _timer->start(0);
    }
}

void RealtimeViewer::stopCamera() {
    if (_capturing) {
        delete _cam;
        _capturing = false;
        _timer->stop();
    }
}
