#pragma once

#include <memory>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>

#include "Camera.h"
#include "MatView.h"

class RealtimeViewer : public QWidget {
    Q_OBJECT
    public:
        RealtimeViewer();
        ~RealtimeViewer(){};
    private slots:
        void handleToggleButton();
        void updateDisplay();
    private:
        QPushButton *_toggleButton;
        QLayout *_layout;
        MatView *_view;
        Camera *_cam;
        bool _capturing;
        QTimer *_timer;

        void startCamera();
        void stopCamera();
};
