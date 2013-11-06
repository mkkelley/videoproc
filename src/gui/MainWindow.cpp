#include "MainWindow.h"

#include <memory>
#include <opencv2/opencv.hpp>
#include <QCoreApplication>
#include <QVBoxLayout>

#include "Camera.h"
#include "CamFilter.h"
#include "CornerDetector.h"
#include "Frame.h"
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

    connect(_realtimeButton, SIGNAL(released()), this, SLOT(handleRealtimeButton()));
    connect(_recordButton, SIGNAL(released()), this, SLOT(handleRecordButton()));
}

MainWindow::~MainWindow() {
}

void MainWindow::handleRealtimeButton() {
    RealtimeViewer *rv = new RealtimeViewer();

    setCentralWidget(rv);
    /*
    CornerDetector cd;
    static auto pFunc = [&cd] (Mat& m) {
        Mat out;
        Frame f(m);
        f.calculate(cd);
        cv::drawKeypoints(m, f.getKeyPoints(), out);
        return out;
    };
    std::unique_ptr<Camera> cam(new Camera(0));
    cam->getSize();
    CamFilter cf(std::move(cam), pFunc);

    cv::namedWindow("realtime feed", CV_WINDOW_AUTOSIZE);
    do {
        Mat image = cf.getNextFrame();
        cv::imshow("realtime feed", image);
    } while (cv::waitKey(1) != 27);
    cv::destroyWindow("realtime feed");
    */
}

void MainWindow::handleRecordButton() {
    _recordButton->setText("Pressed");
}
