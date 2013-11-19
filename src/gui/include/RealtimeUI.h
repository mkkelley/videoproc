#pragma once

#include <QCheckBox>
#include <QPushButton>
#include <QTimer>

#include "MatView.h"
#include "CameraUI.h"

class RealtimeUI : public CameraUI {
    Q_OBJECT;
    public:
        RealtimeUI(QWidget *parent = nullptr);
        ~RealtimeUI();
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
};
