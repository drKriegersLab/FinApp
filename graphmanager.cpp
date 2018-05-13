#include "graphmanager.h"
#include "finapp.h"
#include "ui_finapp.h"
#include <QtCharts/QChartView>
#include <sstream>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QBarSeries>
#include <iostream>


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
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Ft");
    Chart->addAxis(axisY, Qt::AlignLeft);

    // set first and last date time point to determine the necessary range of X axis
    first_date.setDate(QDate(records[0].date->year(), records[0].date->month(), records[0].date->day()));
    last_date.setDate(QDate(records.back().date->year(), records.back().date->month(), records.back().date->day()));
    // add the first data
    num_of_series = 0;
    first_series = addSeries(records);

    // define the base layout
    ParentLayout = Layout;

    // setup
    setTitle(title);

    // creacte chart view object
    ChartView = new QtCharts::QChartView(Chart);

    setAbscissa();

    // give chart to the layout manager
    addChartToLayout();

}


QtCharts::QLineSeries* GraphManager::addSeries(vector<TransactionRecord> records) {
    // get first and last date to modify the range of X axis, if the given data series has larger date range
    QDateTime date_time;
    date_time.setDate(QDate(records[0].date->year(), records[0].date->month(), records[0].date->day()));
    if (date_time < first_date) {
        first_date = date_time;
    }
    date_time.setDate(QDate(records[0].date->year(), records[0].date->month(), records[0].date->day()));
    if (date_time > last_date) {
        last_date = date_time;
    }

    last_date.setDate(QDate(records.back().date->year(), records.back().date->month(), records.back().date->day()));

    // init series
    QtCharts::QLineSeries* Series = new QtCharts::QLineSeries();    
    for (int rec_id = 0; rec_id < records.size(); rec_id++) {
        TransactionRecord rec = records[rec_id];

        date_time.setDate(QDate(rec.date->year(), rec.date->month(), rec.date->day()));
        Series->append(date_time.toMSecsSinceEpoch(), rec.balance);

        // set autorange in y axis
        if ((int)rec.balance < minval_axis_y) {
            minval_axis_y = (int)rec.balance;
        }
        if ((int)rec.balance > maxval_axis_y) {
            maxval_axis_y = (int)rec.balance;
        }

    }
    // set autorange
    axisY->setRange(minval_axis_y, maxval_axis_y);

    // add Series to the Chart and update axes    
    Chart->addSeries(Series);
    Series->attachAxis(axisX);
    Series->attachAxis(axisY);

    // add a name to the series. This name will contain a 5 digits random number and a serial number
    num_of_series++;
    QString series_name = QString::number(tools::generateTimeDependentRandomUInt());
    series_name.append("_");
    series_name.append(QString::number(num_of_series));
    Series->setName(series_name);
    // send a message about the new series
    string message = "added series. Name: ";
    message.append(series_name.toStdString());
    dropDebugPrompt(message );

    //put the series into the container
    series_container.push_back(Series);

    return Series;
}


void GraphManager::setTitle(string title) {
    Chart->setTitle(QString::fromStdString(title));    
}


QtCharts::QLineSeries* GraphManager::getFirstSeries() {
    return first_series;
}

void GraphManager::deleteFirstSeries() {    

    // remove first(base) series from chart
    Chart->removeSeries(first_series);

    // remove the first element from collection
    series_container.erase(series_container.begin());

    // update y axis
    updateOrdinateRange();
}


void GraphManager::deleteAllSeries() {    
    Chart->removeAllSeries();
    series_container.clear();

}

void GraphManager::deleteSeries(QtCharts::QLineSeries *series) {

    // remove series from the chart
    Chart->removeSeries(series);

    // remove series from the collection
    dropDebugPrompt("deleteSeries with given pointer");
    bool flag_found = false;
    for (uint cyc_series = 0; cyc_series < series_container.size(); cyc_series++) {

        if (series_container[cyc_series]->name() == series->name()) {

            series_container.erase(series_container.begin() + cyc_series);
            cout << "\tdeleted" << endl;
            flag_found = true;

            break;
        }
    }

    if (!flag_found) {
        dropDebugPrompt("[ERR] series not found between the associated series");
    }

    // update y Axis
    updateOrdinateRange();
}


/* PRIVATE FUNCTIONS */
void GraphManager::setAbscissa() {
    QtCharts::QLineSeries* Series = new QtCharts::QLineSeries();

    Series->append(first_date.toMSecsSinceEpoch(), 0);
    Series->append(last_date.toMSecsSinceEpoch(), 0);

    Series->setPen(QPen(Qt::black));

    Chart->addSeries(Series);
    Series->attachAxis(axisX);
    Series->attachAxis(axisY);
}


void GraphManager::addChartToLayout() {
    // setup charview object and add it to the given layout
    ChartView->setRenderHint(QPainter::Antialiasing);
    ParentLayout->addWidget(ChartView, 1, 1);
}

void GraphManager::updateOrdinateRange() {
    QtCharts::QLineSeries* series = series_container[0];
    QPointF point = series->at(0);

    minval_axis_y = (int)point.y();
    maxval_axis_y = minval_axis_y;

    for (uint cyc_series = 0; cyc_series < series_container.size(); cyc_series ++) {
        series = series_container[cyc_series];
        cout << "found names: " << series->name().toStdString() << endl;

        for (uint cyc_series_point = 0; cyc_series_point < series->count(); cyc_series_point++) {
            point = series->at(cyc_series_point);

            if ((int)point.y() < minval_axis_y) {
                minval_axis_y = (int)point.y();
            }
            else if ((int)point.y() > maxval_axis_y) {
                maxval_axis_y = (int)point.y();
            }
        }
    }

    axisY->setRange(minval_axis_y, maxval_axis_y);
    //series->attachAxis(axisY);
}

void GraphManager::dropDebugPrompt(string message) {
    cout << "[GraphManager] : " << message << endl;
}

/* PUBLIC STATIC FUNCTION */
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




