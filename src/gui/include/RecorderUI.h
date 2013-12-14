#pragma once

#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QWidget>
#include "CameraUI.h"
#include "VideoStitcher.h"

class RecorderUI : public QWidget {
    Q_OBJECT;
    public:
        RecorderUI(QWidget* parent = nullptr);
        ~RecorderUI() = default;
    private slots:
        void handleToggleButton();
        void recordNextFrame();
    private:
        void startRecording();
        void stopRecording();
        bool isRecording() const;
        void asyncStop();

        QPushButton _toggleButton;
        QLineEdit _fileNameEditor;
        QTimer _timer;
        QCheckBox _analyze;

        VideoStitcher* _stitcher;
        CameraUI _cam;
};
