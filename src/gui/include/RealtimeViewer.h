#pragma once

#include <memory>
#include <QCheckBox>
#include <QLayout>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

#include "Camera.h"
#include "CornerDetector.h"
#include "MatView.h"

class RealtimeViewer : public QWidget {
    Q_OBJECT
    public:
        RealtimeViewer(QWidget *parent = nullptr);
        ~RealtimeViewer();
    private slots:
        void handleToggleButton();
        void updateDisplay();
    private:
        QPushButton *_toggleButton;
        QCheckBox *_analyze;
        QLayout *_layout;
        MatView *_view;
        View *_cam;
        bool _capturing;
        QTimer *_timer;

        static cv::Mat analyzeFrame(cv::Mat&);
        void startCamera();
        void stopCamera();
};
