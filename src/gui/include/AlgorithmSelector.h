#pragma once

#include <map>
#include <QComboBox>

#include "CameraUI.h"

class AlgorithmSelector : public QComboBox {
    public:
        typedef cv::Mat (*transform_fn)(const cv::Mat&);
        AlgorithmSelector(QWidget* parent = nullptr);
        transform_fn getFunction() const;
    private:
        static const std::map<std::string, transform_fn> _algorithms;
};
