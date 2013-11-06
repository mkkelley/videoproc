#include "MainWindow.h"

#include <opencv2/opencv.hpp>
#include <QCoreApplication>
#include <QVBoxLayout>

#include "RealtimeViewer.h"

using std::unique_ptr;
using cv::Mat;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    _centralWidget(new QWidget()),
    _realtimeButton(new QPushButton("Realtime")),
    _recordButton(new QPushButton("Record"))
{
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(_realtimeButton);
    layout->addWidget(_recordButton);

    _centralWidget->setLayout(layout);
    setCentralWidget(_centralWidget);

    connect(_realtimeButton, SIGNAL(released()),
            this, SLOT(handleRealtimeButton()));
    connect(_recordButton, SIGNAL(released()),
            this, SLOT(handleRecordButton()));
}

MainWindow::~MainWindow() {
}

void MainWindow::handleRealtimeButton() {
    RealtimeViewer *rv = new RealtimeViewer();
    setCentralWidget(rv);
}

void MainWindow::handleRecordButton() {
    _recordButton->setText("Pressed");
}
