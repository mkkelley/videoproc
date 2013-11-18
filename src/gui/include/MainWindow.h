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
        void resetMainWindow();
    private:
        void setInterface(QWidget* interface);

        QWidget* _mainMenu;
        QPushButton* _realtimeButton;
        QPushButton* _recordButton;
};
