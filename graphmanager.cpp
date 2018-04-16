#include "graphmanager.h"
#include "finapp.h"
#include "ui_finapp.h"
#include <QtCharts/QChartView>
#include <sstream>

GraphManager::GraphManager(QGridLayout *Layout, vector<TransactionRecord> records, string title) {
    // init series
    Series = new QtCharts::QLineSeries();

    // add the first data
    addSeries(records);

    // define the base layout
    ParentLayout = Layout;

    // setup
    setUpChart();
    setTitle(title);

}

void GraphManager::addSeries(vector<TransactionRecord> records) {
    for (int rec_id = 0; rec_id < records.size(); rec_id++) {
        Series->append(rec_id, records[rec_id].balance);
    }
}

void GraphManager::setUpChart() {
    // create and set up the chart object
    Chart = new QtCharts::QChart();
    Chart->legend()->hide();
    Chart->addSeries(Series);
    Chart->createDefaultAxes();

    // creacte chart view object
    ChartView = new QtCharts::QChartView(Chart);

    addChartToLayout();
}

void GraphManager::addChartToLayout() {
    // setup charview object and add it to the given layout
    ChartView->setRenderHint(QPainter::Antialiasing);
    ParentLayout->addWidget(ChartView, 1, 1);
}

void GraphManager::setTitle(string title) {
    Chart->setTitle(QString::fromStdString(title));
}

void GraphManager::attachNewData(vector<TransactionRecord> records) {
    addSeries(records);
    setUpChart();
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




