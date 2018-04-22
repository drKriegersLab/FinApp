#include "graphmanager.h"
#include "finapp.h"
#include "ui_finapp.h"
#include <QtCharts/QChartView>
#include <sstream>
#include <QDateTime>
#include <QDateTimeAxis>
GraphManager::GraphManager(QGridLayout *Layout, vector<TransactionRecord> records, string title) {

    Chart = new QtCharts::QChart();
    Chart->legend()->hide();

    // set axis X
    axisX = new QtCharts::QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("dd. MM.");
    axisX->setTitleText("Date");
    Chart->addAxis(axisX, Qt::AlignBottom);

    // set axis Y
    axisY = new QtCharts::QValueAxis;
    axisY->setLabelFormat("%z");
    axisY->setTitleText("Ft");
    Chart->addAxis(axisY, Qt::AlignLeft);

    // add the first data
    addSeries(records);

    // define the base layout
    ParentLayout = Layout;

    // setup
    setTitle(title);

    // creacte chart view object
    ChartView = new QtCharts::QChartView(Chart);

    // give chart to the layout manager
    addChartToLayout();

}

void GraphManager::addSeries(vector<TransactionRecord> records) {
    // init series
    //QtCharts::QLineSeries*
    QtCharts::QLineSeries* Series = new QtCharts::QLineSeries();
    cout << "num of records: " << records.size() << endl;
    for (int rec_id = 0; rec_id < records.size(); rec_id++) {

        TransactionRecord rec = records[rec_id];
        QDateTime dateTime;
        dateTime.setDate(QDate(rec.date->year(), rec.date->month(), rec.date->day()));
        //dateTime.setDate(new QDate(rec.date->year(), rec.date->month(), rec.date->day()));
        Series->append(dateTime.toMSecsSinceEpoch(), records[rec_id].balance);
        cout<< "bal2: " << records[rec_id].balance << endl;
    }

    axisY->setRange(-180000,200000);
    Chart->addSeries(Series);
    Series->attachAxis(axisX);
    Series->attachAxis(axisY);
}



void GraphManager::addChartToLayout() {
    // setup charview object and add it to the given layout
    ChartView->setRenderHint(QPainter::Antialiasing);
    ParentLayout->addWidget(ChartView, 1, 1);
}

void GraphManager::setTitle(string title) {
    Chart->setTitle(QString::fromStdString(title));
}



void GraphManager::createGraphChartView(QGridLayout* Layout, vector<TransactionRecord> records, string title){
    // create series
    QtCharts::QLineSeries *Series = new QtCharts::QLineSeries();
    for (int rec_id = 0; rec_id < records.size(); rec_id++) {
        Series->append(rec_id, records[rec_id].balance);
    }

    // create and set up the chart object
    QtCharts::QChart *Chart = new QtCharts::QChart();
    Chart->legend()->hide();
    Chart->addSeries(Series);
    Chart->createDefaultAxes();
    Chart->setTitle(QString::fromStdString(title));

    // creacte chart view object
    QtCharts::QChartView *ChartView = new QtCharts::QChartView(Chart);

    // setup charview object and add it to the given layout
    ChartView->setRenderHint(QPainter::Antialiasing);
    Layout->addWidget(ChartView, 1, 1);
    //return ChartView;
}




