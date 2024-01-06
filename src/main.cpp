#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // TODO: work out how to close
    int a_ret = a.exec();
    w.dataHandler.closeConnections();
    return a_ret;
}
