#include "graphmanager.h"
#include "finapp.h"
#include "ui_finapp.h"
#include <QtCharts/QChartView>

QtCharts::QChartView* GraphManager::createcreateGraphChartView(vector<TransactionRecord> records, string title){
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

    // creacte chart vire object
    QtCharts::QChartView *ChartView = new QtCharts::QChartView(Chart);

    ChartView->setRenderHint(QPainter::Antialiasing);

    return ChartView;
}

/**
 *** FUNCTION FOR FINAPP CLASS. ***
 * **/

void FinApp::showGraphSelectedTransactions(vector<TransactionRecord> transactions){

    // set up the view
    QtCharts::QChartView *chartView = GraphManager::createcreateGraphChartView(transactions, "no title :-(");

    // set up layout
    QGridLayout *ChartLayout = new QGridLayout();
    ChartLayout->addWidget(chartView, 1, 1);
    ui->frame_graphs->setLayout(ChartLayout);
    ui->frame_graphs->setFrameShape(QFrame::NoFrame);

}



