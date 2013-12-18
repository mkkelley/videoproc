#include "RecorderUI.h"

#include <unistd.h>
#include <QtCore>
#include <QVBoxLayout>

#include "Algorithms.h"

RecorderUI::RecorderUI(QWidget *parent)
    : QWidget(parent),
    _toggleButton("Record", this),
    _fileNameEditor(this),
    _analyze("Analyze", this),
    _cam(),
    _pool(new ThreadPool(1)),
    _recorder(_pool, std::unique_ptr<View>(&_cam))
{
    _fileNameEditor.setPlaceholderText("output.avi");

    QVBoxLayout* layout = new QVBoxLayout(this);
    setLayout(layout);
    layout->addWidget(&_fileNameEditor);
    layout->addWidget(&_analyze);
    layout->addWidget(&_toggleButton);

    _cam.addFilter(vp::analyzeFrame);

    connect(&_toggleButton, SIGNAL(released()),
            this, SLOT(handleToggleButton()));
}

RecorderUI::~RecorderUI() {
    _recorder.close();
}

void RecorderUI::handleToggleButton() {
    if (_recorder.isRecording()) {
        _recorder.waitStop();
        _cam.stopCamera();
        _toggleButton.setText("Record");
        return; //EXIT
    } else if (_cam.isCapturing()) {
        _toggleButton.setText("Please Wait");
        _toggleButton.setDown(true);
        _recorder.waitStop();
        _cam.stopCamera();
        return;
    }

    if (_fileNameEditor.text().isEmpty()) {
        _fileNameEditor.setText(_fileNameEditor.placeholderText());
    }
    QString fileName = _fileNameEditor.text();
    _cam.startCamera();
    _recorder.start(fileName.toStdString());

    _toggleButton.setText("Stop");
}
