#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class RecorderUI : public QWidget {
    Q_OBJECT;
    public:
        RecorderUI(QWidget* parent = nullptr);
        ~RecorderUI();
    private slots:
        void handleToggleButton();
    private:
        QPushButton* _toggleButton;
        QLineEdit* _fileNameEditor;
        bool _recording;
};
