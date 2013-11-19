#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include "CameraUI.h"
#include "VideoStitcher.h"

class RecorderUI : public CameraUI {
    Q_OBJECT;
    public:
        RecorderUI(QWidget* parent = nullptr);
        ~RecorderUI();
    private slots:
        void handleToggleButton();
        void recordNextFrame();
    private:
        QPushButton* _toggleButton;
        QLineEdit* _fileNameEditor;
        QTimer _timer;

        VideoStitcher* _stitcher;
};
