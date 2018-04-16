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
    ///init function for creating a totally new chart from the given records
    GraphManager(QGridLayout* Layout, vector<TransactionRecord> records, string title);

    /// function for attaching new data series to the existing chart
    void attachNewData(vector<TransactionRecord> records);

    /// function for set upt the title of the figure
    void setTitle(string title);

    /// static function for creating a totaly new chart separately from the base class
    static void createGraphChartView(QGridLayout* Layout, vector<TransactionRecord> records, string title);


private:
    QGridLayout* ParentLayout; // base layout, where we the object's class is
    QtCharts::QLineSeries* Series; // data series
    QtCharts::QChart* Chart; // chart's object
    QtCharts::QChartView* ChartView; // chart's view object

    /// function for insert new data series
    void addSeries(vector<TransactionRecord> records);

    /// function for setting up the base config
    void setUpChart();

    /// conect our precious chart to the base layout
    void addChartToLayout();

};

#endif // GRAPHMANAGER_H
