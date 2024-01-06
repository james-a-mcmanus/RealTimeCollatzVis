#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "boost/circular_buffer.hpp"

#include "messageParser.h"
#include "SequenceHolder.h"
#include "DataUpdater.h"

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
    void rePlot();
    void refreshData();
    ~MainWindow();
    DataUpdater dataHandler;
    bool refreshing;
    bool doLog;

private slots:
    void timerSlot();
    void on_updateGraph_clicked();
    void on_horizontalSlider_valueChanged(int value);

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QTimer mDataTimer;
};
#endif // MAINWINDOW_H
