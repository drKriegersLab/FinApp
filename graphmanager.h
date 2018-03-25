#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include "xml_parser/database_manager.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>
#include <QtWidgets/QLabel>

/*
 * This class responsible for all graph management task. They are the collection of all necessary data for a graph
 * and creation of a Qchart objec
 * */
class GraphManager
{
public:
    /*
     * init function. It creates a local pointer to the main database manager object.
     * */
    GraphManager(DatabaseManager* DataBaseMng);

    /*
     * this function gets the balances after each transaction and creates a chart from it
     * */
    QtCharts::QChartView* getAllTransactionChartView();




private:
    /* VARIABLE DEFINITIONS */
    DatabaseManager* DbMng; // local copy of the main database's manager

    /* FUNCTIONS */

    /*
     * function for dynamically collection of selected records from the main database
     * */
    void getBalances(int* record_ids[], float* balances[], int num_of_records);

    /*
     * get all transaction and convert them to special chart series
     * */
    QtCharts::QLineSeries* getAllTransactionSeries();


    /*
     * create the graph from the given series and set up some default parameter
     * */
    QtCharts::QChartView* createGraphChart(QtCharts::QLineSeries *Series,  string title);

};

#endif // GRAPHMANAGER_H
