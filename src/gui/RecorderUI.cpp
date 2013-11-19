#include "RecorderUI.h"

#include <QVBoxLayout>

RecorderUI::RecorderUI(QWidget *parent)
    : CameraUI(parent),
    _toggleButton(new QPushButton("Record", this)),
    _fileNameEditor(new QLineEdit(this)),
    _timer(this),
    _stitcher(nullptr)
{
    _fileNameEditor->setPlaceholderText("output.avi");

    QVBoxLayout* layout = new QVBoxLayout(this);
    setLayout(layout);
    layout->addWidget(_fileNameEditor);
    layout->addWidget(_toggleButton);

    connect(_toggleButton, SIGNAL(released()),
            this, SLOT(handleToggleButton()));
    connect(&_timer, SIGNAL(timeout()), this, SLOT(recordNextFrame()));
}

RecorderUI::~RecorderUI() {
}

void RecorderUI::handleToggleButton() {
    if (isCapturing()) {
        _timer.stop();
        delete _stitcher;
        stopCamera();
        return; //EXIT
    }

    if (_fileNameEditor->text().isEmpty()) {
        _fileNameEditor->setText(_fileNameEditor->placeholderText());
    }
    QString fileName = _fileNameEditor->text();

    startCamera();
    _stitcher = new VideoStitcher(fileName.toStdString(), _cam->getFps());
    _timer.start(1);
}

void RecorderUI::recordNextFrame() {
    if (_stitcher == nullptr) {
        return;
    }
    _stitcher->appendImage(_cam->getNextFrame());
}
