#pragma once

#include <QLabel>
#include <opencv2/opencv.hpp>

class MatView : public QLabel {
    Q_OBJECT

    public:
        MatView(const cv::Mat&, QWidget *parent = nullptr);
        MatView(QWidget *parent = nullptr);
        ~MatView(){};
        void setMat(const cv::Mat&);
};
