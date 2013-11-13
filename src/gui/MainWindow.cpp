#include "MainWindow.h"

#include <opencv2/opencv.hpp>
#include <QCoreApplication>
#include <QVBoxLayout>

#include "RealtimeViewer.h"

using cv::Mat;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    resetMainWindow();
}

MainWindow::~MainWindow() {
}

void MainWindow::handleRealtimeButton() {
    auto* realtimeInterface = new QWidget(this);
    auto* backButton = new QPushButton("Back", realtimeInterface);
    auto* rv = new RealtimeViewer(realtimeInterface);

    auto* vlayout = new QVBoxLayout();
    vlayout->addWidget(backButton);
    vlayout->addWidget(rv);
    realtimeInterface->setLayout(vlayout);

    connect(backButton, SIGNAL(released()),
            this, SLOT(resetMainWindow()));

    setCentralWidget(realtimeInterface);
}

void MainWindow::handleRecordButton() {
    _recordButton->setText("Pressed");
}

void MainWindow::resetMainWindow() {
    _mainMenu = new QWidget(this);
    _realtimeButton = new QPushButton("Realtime", _mainMenu);
    _recordButton = new QPushButton("Record", _mainMenu);
    auto* layout = new QVBoxLayout();
    layout->addWidget(_realtimeButton);
    layout->addWidget(_recordButton);
    _mainMenu->setLayout(layout);
    setCentralWidget(_mainMenu);
    adjustSize();
    connect(_realtimeButton, SIGNAL(released()),
            this, SLOT(handleRealtimeButton()));
    connect(_recordButton, SIGNAL(released()),
            this, SLOT(handleRecordButton()));
}
