#include "RealtimeViewer.h"

#include <QLayout>
#include "Frame.h"

using cv::Mat;

RealtimeViewer::RealtimeViewer(QWidget *parent)
    : CameraUI(parent),
    _toggleButton(new QPushButton("Stop", this)),
    _analyze(new QCheckBox("Analyze", this)),
    _view(new MatView(this)),
    _timer(new QTimer(this))
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(_view);

    auto buttons = new QHBoxLayout();
    buttons->addWidget(_toggleButton);
    buttons->addWidget(_analyze);

    layout->addLayout(buttons); //layout takes ownership of buttons, don't delete
    setLayout(layout); //QWidget takes ownership of layout, don't delete

    connect(_toggleButton, SIGNAL(released()), this, SLOT(handleToggleButton()));
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateDisplay()));
    startCamera();
}

RealtimeViewer::~RealtimeViewer() {
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

Mat RealtimeViewer::analyzeFrame(Mat& inp) {
    static CornerDetector cd;
    Mat out;
    Frame f(inp);
    f.calculate(cd);
    cv::drawKeypoints(inp, f.getKeyPoints(), out);
    return out;
}

void RealtimeViewer::afterStart() {
    _cam->addFilter(analyzeFrame);
    _timer->start(0);
}

void RealtimeViewer::afterStop() {
    _timer->stop();
}
