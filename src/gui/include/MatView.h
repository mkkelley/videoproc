#pragma once

#include <QLabel>
#include <opencv2/opencv.hpp>

class MatView : public QLabel {
    Q_OBJECT

    public:
        MatView(const cv::Mat&, QWidget *parent = 0);
        MatView(QWidget *parent = 0);
        ~MatView(){};
        void setMat(const cv::Mat&);
};
