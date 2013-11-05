#include "MatView.h"

#include <iostream>
using std::cout;
using std::endl;

using cv::Mat;

MatView::MatView(const Mat& mat, QWidget *parent)
    : QLabel(parent)
{
    Mat tmp;
    cv::cvtColor(mat, tmp, CV_BGR2RGB);
    QImage image(
            (uchar*)tmp.data,
            tmp.cols,
            tmp.rows,
            QImage::Format_RGB888);
    cout << image.width() << endl;
    cout << image.bytesPerLine() << endl;
    cout << tmp.step << endl;
    //QImage i2(image);
    //i2.detach();
    QPixmap pixmap = QPixmap::fromImage(image);
    setPixmap(pixmap);
}