#pragma once

#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QWidget>
#include "CameraUI.h"
#include "VideoStitcher.h"

class RecorderUI : public CameraUI {
    Q_OBJECT;
    public:
        RecorderUI(QWidget* parent = nullptr);
        ~RecorderUI() = default;
    private slots:
        void handleToggleButton();
        void recordNextFrame();
    private:
        QPushButton* _toggleButton;
        QLineEdit* _fileNameEditor;
        QTimer _timer;
        QCheckBox _analyze;

        VideoStitcher* _stitcher;
};
