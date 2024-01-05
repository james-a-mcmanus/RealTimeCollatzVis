#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void generateData();
    ~MainWindow();

private slots:
    void on_updateGraph_clicked();
    void timerSlot();

private:
    Ui::MainWindow *ui;
    QTimer mDataTimer;
    int counter;
};
#endif // MAINWINDOW_H
