#include "mainwindow.h"
#include "qcustomplot.h"
#include "ui_mainwindow.h"
#include "boost/circular_buffer.hpp"

#include <iostream>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <iomanip>

#include <thread>
#include <chrono>

#include "messageParser.h"
#include "SequenceHolder.h"
#include "DataUpdater.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , dataHandler(100, 100)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    mDataTimer.start(200);
    dataHandler.initialise();
}

MainWindow::~MainWindow()
{
    delete ui;
};

void MainWindow::generateData(){
    // generate some data:
    QVector<double> x(100), y(100); // initialize with entries 0..100
    for (int i=0; i<100; ++i)
    {
        x[i] = i/50.0 - 1; // x goes from -1 to 1
        y[i] = x[i]*x[i]; // let's plot a quadratic function
    };
    // create graph and assign data to it:
    ui->graph->addGraph();
    ui->graph->graph(0)->setData(x,y);//(0)->setData(x, y);
    // give the axes some labels:
    ui->graph->xAxis->setLabel("x");
    ui->graph->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->graph->xAxis->setRange(-4, 4);
    ui->graph->yAxis->setRange(-4, 5);
    ui->graph->replot();
}

void MainWindow::on_updateGraph_clicked()
{
    this->generateData();
}


void MainWindow::timerSlot(){
    this->generateData();
}
