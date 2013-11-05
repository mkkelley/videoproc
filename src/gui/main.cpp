#include "MainWindow.h"

#include <QApplication>

int main(int argc, char **argv) {
    QApplication qapp(argc, argv);
    MainWindow mw;
    mw.show();
    return qapp.exec();
}
