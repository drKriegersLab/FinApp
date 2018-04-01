#include "graphmanager.h"
#include "finapp.h"
#include "ui_finapp.h"
#include <QtCharts/QChartView>

GraphManager::GraphManager(DatabaseManager* DataBaseMng) {
    DbMng = DataBaseMng;
}

void GraphManager::getBalances(int *record_ids[], float *balances[], int num_of_records) {
    /* local variables */
    int *ids = new int[num_of_records];
    float *bals = new float[num_of_records];

    /* iterating over each specified transaction and collect its balances */
    TransactionRecord transaction;

    for(int record_id = 0; record_id < num_of_records; record_id++) {
        ids[record_id] = record_id;
        DbMng->getTransaction(record_id, &transaction);
        bals[record_id] = transaction.balance;
        //cout << "[GraphManager] : balance: " << transaction.balance << endl;
    }

    /* return the pointer of IDs an balances of each transaction */
    *record_ids = ids;
    *balances = bals;
}


QtCharts::QLineSeries* GraphManager::getAllTransactionSeries() {
    /* local variables */
    int* ids;
    float* bals;
    int num_of_records = DbMng->getNumOfTransactions();

    /* get all balances */
    getBalances(&ids, &bals, num_of_records);

    /* create a QT series from the balances */
    QtCharts::QLineSeries *Series = new QtCharts::QLineSeries();

    for (int record_id = 0; record_id < num_of_records; record_id++) {
        Series->append(ids[record_id], bals[record_id]);
    }

    return Series;
}

QtCharts::QChartView* GraphManager::createGraphChart(QtCharts::QLineSeries *Series,  string title){
    /* create and set up the chart object */
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

QtCharts::QChartView* GraphManager::getAllTransactionChartView() {
    return createGraphChart(getAllTransactionSeries(), "all transactions");
}

/**
 *** FUNCTION FOR FINAPP CLASS. ***
 * **/

void FinApp::showGraphAllTransactions() {
    // create the chart
    //QtCharts::QChartView *chartView = new QtCharts::QChartView(GraphMng->getGraphAllTransaction());
        //QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    // set up the view
    //chartView->setRenderHint(QPainter::Antialiasing);
    QtCharts::QChartView *chartView = GraphMng->getAllTransactionChartView();

    //QWidget *popup = new QWidget;
    //popup->close();
    //chartView->scene()->addWidget(popup);


    QGridLayout *ChartLayout = new QGridLayout(this);
    ChartLayout->addWidget(chartView, 1, 1);


    ui->frame_graphs->setLayout(ChartLayout);
    ui->frame_graphs->setFrameShape(QFrame::NoFrame);

}


