#include "MatView.h"

#include <iostream>
using std::cout;
using std::endl;

using cv::Mat;

MatView::MatView(const Mat& mat, QWidget *parent)
    : QLabel(parent)
{
    setMat(mat);
}

MatView::MatView(QWidget *parent)
    : QLabel(parent)
{
}

void MatView::setMat(const Mat& mat) {
    Mat tmp;
    cv::cvtColor(mat, tmp, CV_BGR2RGB);
    QImage image(
            (uchar*)tmp.data,
            tmp.cols,
            tmp.rows,
            QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(image);
    setPixmap(pixmap);
}
