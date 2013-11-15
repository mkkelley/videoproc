#include "RecorderViewer.h"

#include <QVBoxLayout>

RecorderViewer::RecorderViewer(QWidget *parent)
    : QWidget(parent),
    _toggleButton(new QPushButton("Record"))
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    setLayout(layout);
    layout->addWidget(_toggleButton);
}

RecorderViewer::~RecorderViewer() {

}
