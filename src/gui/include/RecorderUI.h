#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "CameraUI.h"

class RecorderUI : public CameraUI {
    Q_OBJECT;
    public:
        RecorderUI(QWidget* parent = nullptr);
        ~RecorderUI();
    private slots:
        void handleToggleButton();
    private:
        QPushButton* _toggleButton;
        QLineEdit* _fileNameEditor;
};
