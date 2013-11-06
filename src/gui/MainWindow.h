#pragma once

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
    private slots:
        void handleRealtimeButton();
        void handleRecordButton();
    private:
        QWidget *_centralWidget;
        QPushButton *_realtimeButton;
        QPushButton *_recordButton;
};
