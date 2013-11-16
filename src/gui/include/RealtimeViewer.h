#pragma once

#include <QCheckBox>
#include <QPushButton>
#include <QTimer>

#include "MatView.h"
#include "CameraUI.h"

class RealtimeViewer : public CameraUI {
    Q_OBJECT;
    public:
        RealtimeViewer(QWidget *parent = nullptr);
        ~RealtimeViewer();
    private slots:
        void handleToggleButton();
        void updateDisplay();
        void afterStart() override;
        void afterStop() override;
    private:
        QPushButton* _toggleButton;
        QCheckBox* _analyze;
        MatView* _view;
        QTimer* _timer;

        static cv::Mat analyzeFrame(cv::Mat&);
};
