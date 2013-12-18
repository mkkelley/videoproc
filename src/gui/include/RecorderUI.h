#pragma once

#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QWidget>
#include "CameraUI.h"
#include "AsyncRecorder.h"

class RecorderUI : public QWidget {
    Q_OBJECT;
    public:
        RecorderUI(QWidget* parent = nullptr);
        ~RecorderUI();
    private slots:
        void handleToggleButton();
    private:
        QPushButton _toggleButton;
        QLineEdit _fileNameEditor;
        QCheckBox _analyze;

        CameraUI _cam;
        std::shared_ptr<ThreadPool> _pool;
        AsyncRecorder _recorder;
};
