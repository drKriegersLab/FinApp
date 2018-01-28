#include "graphmanager.h"

GraphManager::GraphManager(DatabaseManager* DataBaseMng) {
    DbMng = DataBaseMng;
}

QtCharts::QChart* GraphManager::getGraphAllTransaction() {
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

    /* create and set up the chart object */
    QtCharts::QChart *Chart = new QtCharts::QChart();
    Chart->legend()->hide();
    Chart->addSeries(Series);
    Chart->createDefaultAxes();
    Chart->setTitle("all transactions");

    return Chart;
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
        cout << "[GraphManager] : balance: " << transaction.balance << endl;
    }

    /* return the pointer of IDs an balances of each transaction */
    *record_ids = ids;
    *balances = bals;
}
