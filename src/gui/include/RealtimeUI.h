#pragma once

#include <QCheckBox>
#include <QPushButton>
#include <QTimer>

#include "MatView.h"
#include "CameraUI.h"

class RealtimeUI : public QWidget {
    Q_OBJECT;
    public:
        RealtimeUI(QWidget *parent = nullptr);
        ~RealtimeUI() = default;
    private slots:
        void handleToggleButton();
        void updateDisplay();
    private:
        QPushButton* _toggleButton;
        QCheckBox* _analyze;
        MatView* _view;
        QTimer* _timer;
        CameraUI _cam;
};
