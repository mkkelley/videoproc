#include "RealtimeUI.h"

#include <QLayout>
#include "Frame.h"

using cv::Mat;

RealtimeUI::RealtimeUI(QWidget *parent)
    : QWidget(parent),
    _toggleButton("Stop", this),
    _analyze("Analyze", this),
    _view(this),
    _timer(this),
    _cam(),
    _algoSelect(this)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(&_view);

    auto buttons = new QHBoxLayout();
    buttons->addWidget(&_toggleButton);
    buttons->addWidget(&_algoSelect);
    buttons->addWidget(&_analyze);

    layout->addLayout(buttons);
    setLayout(layout);

    _cam.afterStart([this](){_timer.start(0);});
    _cam.afterStop([this](){_timer.stop();});
    _cam.startCamera();

    connect(&_toggleButton, SIGNAL(released()), this, SLOT(handleToggleButton()));
    connect(&_timer, SIGNAL(timeout()), this, SLOT(updateDisplay()));
    connect(&_analyze, SIGNAL(stateChanged(int)), this, SLOT(handleAnalyzeToggle()));
}

void RealtimeUI::updateDisplay() {
    if (!_cam.isCapturing()) {
        return;
    }
    Mat f = _cam.getNextFrame();
    _view.setMat(f);
}

void RealtimeUI::handleToggleButton() {
    if (_cam.isCapturing()) {
        _toggleButton.setText("Start");
        _cam.stopCamera();
    } else {
        _toggleButton.setText("Stop");
        _cam.startCamera();
    }
}

void RealtimeUI::handleAnalyzeToggle() {
    _cam.clearFilters();
    if (_analyze.isChecked()) {
        _cam.addFilter(_algoSelect.getFunction());
    }
}
