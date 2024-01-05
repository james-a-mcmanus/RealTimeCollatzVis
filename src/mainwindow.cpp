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

void MainWindow::rePlot(){
    // generate some data:

    std::cout << this->dataHandler.front() << std::endl;
    //boost::circular_buffer<double> seq = ;
    for (auto it = this->dataHandler.begin(); it != this->dataHandler.end(); ++it){
        std::cout << *it;
    }
    std::cout << std::endl;

    int num_data = this->dataHandler.sequence.size();
    QVector<double> data(num_data);

    QVector<double> x(data.size()); // initialize with entries 0..100
    // create graph and assign data to it:
    ui->graph->addGraph();
    ui->graph->graph(0)->setData(x,data);//(0)->setData(x, y);
    // give the axes some labels:
    ui->graph->xAxis->setLabel("x");
    ui->graph->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->graph->xAxis->setRange(0, 100);
    ui->graph->yAxis->setRange(0, 200);
    ui->graph->replot();
}



void MainWindow::timerSlot(){
    this->refreshData();
    std::cout << this->dataHandler.front() << std::endl;
    this->rePlot();
}


void MainWindow::refreshData(){
    dataHandler.receiveMessage();
    dataHandler.addFromMessage();
    //QVector<...> qVec = QVector<...>(stdVec.begin(), stdVec.end());
}
