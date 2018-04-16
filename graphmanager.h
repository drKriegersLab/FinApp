#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include "xml_parser/database_manager.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>
#include <QtWidgets/QLabel>
#include <QGridLayout>

/*
 * This class responsible for all graph management and manipulation tasks
 * */
class GraphManager
{
public:


    static void createGraphChartView(QGridLayout* Layout, vector<TransactionRecord> records, string title);


private:

};

#endif // GRAPHMANAGER_H
