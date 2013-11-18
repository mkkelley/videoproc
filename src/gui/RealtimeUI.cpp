#include "RealtimeUI.h"

#include <QLayout>
#include "Frame.h"

using cv::Mat;

RealtimeUI::RealtimeUI(QWidget *parent)
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

RealtimeUI::~RealtimeUI() {
}

void RealtimeUI::updateDisplay() {
    if (!isCapturing()) {
        return;
    }
    Mat f = _analyze->isChecked() ? _cam->getNextFrame() : _cam->getNextRawFrame();
    _view->setMat(f);
}

void RealtimeUI::handleToggleButton() {
    if (isCapturing()) {
        _toggleButton->setText("Start");
        stopCamera();
    } else {
        _toggleButton->setText("Stop");
        startCamera();
    }
}

Mat RealtimeUI::analyzeFrame(Mat& inp) {
    static CornerDetector cd;
    Mat out;
    Frame f(inp);
    f.calculate(cd);
    cv::drawKeypoints(inp, f.getKeyPoints(), out);
    return out;
}

void RealtimeUI::afterStart() {
    _cam->addFilter(analyzeFrame);
    _timer->start(0);
}

void RealtimeUI::afterStop() {
    _timer->stop();
}
