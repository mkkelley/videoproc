#include "RealtimeViewer.h"

#include "Frame.h"

using cv::Mat;

RealtimeViewer::RealtimeViewer(QWidget *parent)
    : QWidget(parent),
    _toggleButton(new QPushButton("Stop", this)),
    _analyze(new QCheckBox("Analyze", this)),
    _layout(new QVBoxLayout()),
    _view(new MatView(this)),
    _capturing(false),
    _timer(new QTimer(this))
{
    _layout->addWidget(_view);

    auto *buttons = new QHBoxLayout();
    buttons->addWidget(_toggleButton);
    buttons->addWidget(_analyze);

    static_cast<QVBoxLayout*>(_layout)->addLayout(buttons);
    setLayout(_layout);

    connect(_toggleButton, SIGNAL(released()), this, SLOT(handleToggleButton()));
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateDisplay()));
    startCamera();
}

RealtimeViewer::~RealtimeViewer() {
    stopCamera();
}

void RealtimeViewer::updateDisplay() {
    if (!_capturing) {
        return;
    }
    Mat f = _analyze->isChecked() ? _cam->getNextFrame() : _cam->getNextRawFrame();
    _view->setMat(f);
}

void RealtimeViewer::handleToggleButton() {
    if (_capturing) {
        _toggleButton->setText("Start");
        stopCamera();
    } else {
        _toggleButton->setText("Stop");
        startCamera();
    }
}

void RealtimeViewer::startCamera() {
    if (_capturing) {
        return;
    }
    _cam = new Camera(0);
    _cam->addFilter(analyzeFrame);
    _capturing = true;
    _timer->start(0);
}

Mat RealtimeViewer::analyzeFrame(Mat& inp) {
    static CornerDetector cd;
    Mat out;
    Frame f(inp);
    f.calculate(cd);
    cv::drawKeypoints(inp, f.getKeyPoints(), out);
    return out;
}

void RealtimeViewer::stopCamera() {
    if (!_capturing) {
        return;
    }
    delete _cam;
    _capturing = false;
    _timer->stop();
}
