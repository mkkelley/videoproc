#pragma once

#include <memory>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>

#include "Camera.h"
#include "CornerDetector.h"
#include "MatView.h"

class RealtimeViewer : public QWidget {
    Q_OBJECT
    public:
        RealtimeViewer(QWidget *parent = 0);
        ~RealtimeViewer();
    private slots:
        void handleToggleButton();
        void updateDisplay();
    private:
        QPushButton *_toggleButton;
        QLayout *_layout;
        MatView *_view;
        View *_cam;
        bool _capturing;
        QTimer *_timer;

        static cv::Mat analyzeFrame(cv::Mat&);
        void startCamera();
        void stopCamera();
};
