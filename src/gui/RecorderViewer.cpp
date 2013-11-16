#include "RecorderViewer.h"

#include <QVBoxLayout>

RecorderViewer::RecorderViewer(QWidget *parent)
    : QWidget(parent),
    _toggleButton(new QPushButton("Record")),
    _fileNameEditor(new QLineEdit(this)),
    _recording(false)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    setLayout(layout);
    layout->addWidget(_fileNameEditor);
    layout->addWidget(_toggleButton);
}

RecorderViewer::~RecorderViewer() {

}

void RecorderViewer::handleToggleButton() {
    QString fileName = _fileNameEditor->text();
    if (fileName.isEmpty()) {
        fileName = "output.avi";
        _fileNameEditor->setText(fileName);
    }
}
