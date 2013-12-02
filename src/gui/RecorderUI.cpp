#include "RecorderUI.h"

#include <unistd.h>
#include <QtCore>
#include <QVBoxLayout>

RecorderUI::RecorderUI(QWidget *parent)
    : CameraUI(parent),
    _toggleButton("Record", this),
    _fileNameEditor(this),
    _timer(this),
    _analyze("Analyze", this),
    _stitcher(nullptr)
{
    _fileNameEditor.setPlaceholderText("output.avi");

    QVBoxLayout* layout = new QVBoxLayout(this);
    setLayout(layout);
    layout->addWidget(&_fileNameEditor);
    layout->addWidget(&_analyze);
    layout->addWidget(&_toggleButton);

    connect(&_toggleButton, SIGNAL(released()),
            this, SLOT(handleToggleButton()));
    connect(&_timer, SIGNAL(timeout()),
            this, SLOT(recordNextFrame()));
}

void RecorderUI::startRecording() {
    QString fileName = _fileNameEditor.text();
    startCamera();
    _cam->addFilter(vp::analyzeFrame);
    _stitcher = new VideoStitcher(fileName.toStdString(), _cam->getFps());
    _timer.start(1);
}

void RecorderUI::stopRecording() {
    _timer.stop();
    delete _stitcher;
    stopCamera();
}

bool RecorderUI::isRecording() const {
    return _timer.isActive();
}

void RecorderUI::asyncStop() {
    while (!isRecording() && isCapturing()) {
        usleep(500);
    }
    stopRecording();
    _toggleButton.setText("Record");
    _toggleButton.setDown(false);
}

void RecorderUI::handleToggleButton() {
    if (isRecording()) {
        stopRecording();
        _toggleButton.setText("Record");
        return; //EXIT
    } else if (isCapturing()) {
        _toggleButton.setText("Please Wait");
        _toggleButton.setDown(true);
        QtConcurrent::run(std::bind(&RecorderUI::asyncStop, this));
        return;
    }

    if (_fileNameEditor.text().isEmpty()) {
        _fileNameEditor.setText(_fileNameEditor.placeholderText());
    }
    QString fileName = _fileNameEditor.text();
    QtConcurrent::run(std::bind(&RecorderUI::startRecording, this));

    _toggleButton.setText("Stop");
}

void RecorderUI::recordNextFrame() {
    if (_stitcher == nullptr) {
        return;
    }
    _stitcher->appendImage(
            _analyze.isChecked() ?
                _cam->getNextFrame() :
                _cam->getNextRawFrame()
    );
}
