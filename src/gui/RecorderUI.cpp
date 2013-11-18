#include "RecorderUI.h"

#include <QVBoxLayout>

RecorderUI::RecorderUI(QWidget *parent)
    : CameraUI(parent),
    _toggleButton(new QPushButton("Record", this)),
    _fileNameEditor(new QLineEdit(this)),
    _recording(false)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    setLayout(layout);
    layout->addWidget(_fileNameEditor);
    layout->addWidget(_toggleButton);
}

RecorderUI::~RecorderUI() {
}

void RecorderUI::handleToggleButton() {
    QString fileName = _fileNameEditor->text();
    if (fileName.isEmpty()) {
        fileName = "output.avi";
        _fileNameEditor->setText(fileName);
    }
    startCamera();
}
