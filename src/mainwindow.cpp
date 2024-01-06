#include "mainwindow.h"
#include "qcustomplot.h"
#include "ui_mainwindow.h"
#include "boost/circular_buffer.hpp"

//#include <iostream>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
//#include <cstring>
//#include <vector>
//#include <iomanip>

//#include <thread>
//#include <chrono>

//#include "messageParser.h"
//#include "SequenceHolder.h"
#include "DataUpdater.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , dataHandler(100, 100)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graph->addGraph();
    ui->graph->xAxis->setLabel("Time");
    ui->graph->yAxis->setLabel("Sequence");

    // Colours:
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    ui->graph->axisRect()->setBackground(axisRectGradient);
    ui->graph->setBackground(axisRectGradient);
    QPen pen(QColor(70, 200, 70));
    pen.setWidth(2);
    ui->graph->graph(0)->setPen(pen);
    ui->graph->graph(0)->setBrush(QBrush(QColor(70, 200, 70, 60)));
    ui->graph->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->graph->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->graph->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->graph->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->graph->xAxis->setTickLabelColor(Qt::white);
    ui->graph->yAxis->setTickLabelColor(Qt::white);
    ui->graph->xAxis->setLabelColor(Qt::white);
    ui->graph->yAxis->setLabelColor(Qt::white);
    ui->graph->xAxis->grid()->setSubGridVisible(true);
    ui->graph->yAxis->grid()->setSubGridVisible(true);

    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    mDataTimer.start(50);
    dataHandler.initialise();
    refreshing=true;
}

MainWindow::~MainWindow()
{
    delete ui;
};

void MainWindow::rePlot(){
    // generate some data:

    QVector<double> x(this->dataHandler.size()); // initialize with entries 0..100   
    QVector<double> data(this->dataHandler.size()); // initialize with entries 0..100       
    
    // populate the chart QVectors.
    int i0 = 0;
    for (auto it = this->dataHandler.begin(); it != this->dataHandler.end(); ++it){
        data[i0] = *it;
        x[i0] = i0;
        i0++;
    }

    // create graph and assign data to it:
    ui->graph->graph(0)->setData(x,data);//(0)->setData(x, y);
    // give the axes some labels:
    // set axes ranges, so we see all data:
    ui->graph->xAxis->setRange(0, 100);
    ui->graph->yAxis->setRange(0, *std::max_element(data.constBegin(), data.constEnd()));
    ui->graph->replot();
}



void MainWindow::timerSlot(){
    this->refreshData();
    if (this->refreshing){
        this->rePlot();
    }
}


void MainWindow::refreshData(){
    dataHandler.addFromMessage();
}

void MainWindow::on_updateGraph_clicked()
{
    refreshing = !refreshing;
}

