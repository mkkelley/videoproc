#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class RecorderViewer : public QWidget {
    Q_OBJECT;
    public:
        RecorderViewer(QWidget* parent = nullptr);
        ~RecorderViewer();
    private slots:
        void handleToggleButton();
    private:
        QPushButton* _toggleButton;
        QLineEdit* _fileNameEditor;
        bool _recording;
};
