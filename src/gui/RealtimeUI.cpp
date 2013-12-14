#include "RealtimeUI.h"

#include <QLayout>
#include "Frame.h"

using cv::Mat;

RealtimeUI::RealtimeUI(QWidget *parent)
    : QWidget(parent),
    _toggleButton(new QPushButton("Stop", this)),
    _analyze(new QCheckBox("Analyze", this)),
    _view(new MatView(this)),
    _timer(new QTimer(this)),
    _cam()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(_view);

    auto buttons = new QHBoxLayout();
    buttons->addWidget(_toggleButton);
    buttons->addWidget(_analyze);

    layout->addLayout(buttons); //layout takes ownership of buttons, don't delete
    setLayout(layout); //QWidget takes ownership of layout, don't delete

    _cam.afterStart([this](){_timer->start(0);});
    _cam.afterStop([this](){_timer->stop();});
    _cam.addFilter(vp::analyzeFrame);
    _cam.startCamera();

    connect(_toggleButton, SIGNAL(released()), this, SLOT(handleToggleButton()));
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateDisplay()));
}

void RealtimeUI::updateDisplay() {
    if (!_cam.isCapturing()) {
        return;
    }
    Mat f = _analyze->isChecked() ? _cam.getNextFrame() : _cam.getNextRawFrame();
    _view->setMat(f);
}

void RealtimeUI::handleToggleButton() {
    if (_cam.isCapturing()) {
        _toggleButton->setText("Start");
        _cam.stopCamera();
    } else {
        _toggleButton->setText("Stop");
        _cam.startCamera();
    }
}
