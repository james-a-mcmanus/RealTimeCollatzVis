#include "mainwindow.h"
#include "qcustomplot.h"
#include "ui_mainwindow.h"

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <math.h>

#include "DataUpdater.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , dataHandler(350, 7, 50)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graph->addGraph();

    // Setup the axis labels and range.
    ui->graph->xAxis->setLabel("Time");
    ui->graph->yAxis->setLabel("Sequence");
    ui->graph->xAxis->setRange(0, 350);

    // Set the graph appearence:
    // Plot background colour
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    ui->graph->axisRect()->setBackground(axisRectGradient);
    ui->graph->setBackground(axisRectGradient);

    // Line pen properties
    QPen pen(QColor(70, 200, 70));
    pen.setWidth(2);
    ui->graph->graph(0)->setPen(pen);
    ui->graph->graph(0)->setBrush(QBrush(QColor(70, 200, 70, 60)));

    // Axis appearance
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

    // Update the graph with a timer.
    dataHandler.initialise();
    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    ui->sliderLabel->setText(QString("10"));
    mDataTimer.start(10);
    refreshing=true;
    doLog = false;
}

MainWindow::~MainWindow()
{
    delete ui;
};

// Refresh the graph on the screen.
void MainWindow::rePlot(){

    // create qvectors for plotting.
    QVector<double> x(this->dataHandler.size());
    QVector<double> data(this->dataHandler.size());
    
    // populate the chart QVectors.
    int i0 = 0;
    for (auto it = this->dataHandler.begin(); it != this->dataHandler.end(); ++it){
        if (this->doLog){
            data[i0] = log(*it);
        }
        else {
            data[i0] = *it;
        }
        x[i0] = i0;
        i0++;
    }

    // assign data to the graph
    ui->graph->graph(0)->setData(x,data);//(0)->setData(x, y);

    // set y axis range, so we see all data:
    ui->graph->yAxis->setRange(0, *std::max_element(data.constBegin(), data.constEnd()));

    // plot
    ui->graph->replot();
}

// Update the data and replot
void MainWindow::timerSlot(){
    this->refreshData();
    if (this->refreshing){
        this->rePlot();
    }
}

// Get new data from the socket.
void MainWindow::refreshData(){
    dataHandler.addFromMessage();
}

// Toggle on/off graph updating.
void MainWindow::on_updateGraph_clicked()
{
    refreshing = !refreshing;
}

//
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    this->mDataTimer.setInterval(value);
    ui->sliderLabel->setText(QString::number(value));
}

//
void MainWindow::on_checkBox_stateChanged(int arg1)
{
    this->doLog = !this->doLog;
}

