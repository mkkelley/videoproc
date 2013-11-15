#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class RecorderViewer : public QWidget {
    Q_OBJECT
    public:
        RecorderViewer(QWidget* parent = nullptr);
        ~RecorderViewer();
    private:
        QPushButton* _toggleButton;
        QLineEdit* _fileName;
};
