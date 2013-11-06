#pragma once

#include <memory>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "Camera.h"
#include "MatView.h"

class RealtimeViewer : public QWidget {
    Q_OBJECT
    public:
        RealtimeViewer();
        ~RealtimeViewer(){};
    private slots:
        void handleToggleButton();
    private:
        QPushButton *_toggleButton;
        QLayout *_layout;
        MatView *_view;
        std::unique_ptr<Camera> _cam;
};
