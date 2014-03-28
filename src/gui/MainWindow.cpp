#include "MainWindow.h"

#include <opencv2/opencv.hpp>
#include <QCoreApplication>
#include <QVBoxLayout>

#include "RealtimeUI.h"
#include "RecorderUI.h"

using cv::Mat;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    resetMainWindow();
}

void MainWindow::resetMainWindow() {
    _mainMenu = new QWidget(this);
    _realtimeButton = new QPushButton("Realtime", _mainMenu);
    //_recordButton = new QPushButton("Record", _mainMenu);
    auto* layout = new QVBoxLayout();
    layout->addWidget(_realtimeButton);
    //layout->addWidget(_recordButton);
    _mainMenu->setLayout(layout);
    setCentralWidget(_mainMenu);
    adjustSize();
    connect(_realtimeButton, SIGNAL(released()),
            this, SLOT(handleRealtimeButton()));
    //connect(_recordButton, SIGNAL(released()),
            //this, SLOT(handleRecordButton()));
}

void MainWindow::setInterface(QWidget* interface) {
    QWidget* container = new QWidget(this);
    QPushButton* backButton = new QPushButton("Back", container);
    interface->setParent(container);

    QLayout* containerLayout = new QVBoxLayout(container);
    containerLayout->addWidget(backButton);
    containerLayout->addWidget(interface);
    container->setLayout(containerLayout);

    connect(backButton, SIGNAL(released()),
            this, SLOT(resetMainWindow()));

    setCentralWidget(container);
}

void MainWindow::handleRealtimeButton() {
    auto* realtimeViewer = new RealtimeUI();
    setInterface(realtimeViewer);
}

void MainWindow::handleRecordButton() {
    auto* recorderViewer = new RecorderUI();
    setInterface(recorderViewer);
}
