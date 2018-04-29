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
#include <QDateTimeAxis>
#include <QBarCategoryAxis>

/*
 * This class responsible for all graph management and manipulation tasks
 * */
class GraphManager
{
public:
    ///init function for creating a totally new chart from the given records
    GraphManager(QGridLayout* Layout, vector<TransactionRecord> records, string title);

    /// function for insert new data series
    QtCharts::QLineSeries* addSeries(vector<TransactionRecord> records);


    /// function for set upt the title of the figure
    void setTitle(string title);

    QtCharts::QLineSeries* getFirstSeries();

    /// static function for creating a totaly new chart separately from the base class
    static void createGraphChartView(QGridLayout* Layout, vector<TransactionRecord> records, string title);         


private:
    /* PRIVATE VARIABLES */
    QtCharts::QDateTimeAxis *axisX;
    QtCharts::QValueAxis *axisY;
    int minval_axis_y = 0;
    int maxval_axis_y = 0;

    QDateTime first_date;
    QDateTime last_date;

    QGridLayout* ParentLayout; // base layout, where we the object's class is
    QtCharts::QLineSeries* Series; // data series
    QtCharts::QChart* Chart; // chart's object
    QtCharts::QChartView* ChartView; // chart's view object

    QtCharts::QLineSeries* first_series;

    /* PRIVATE FUNCTIONS */
    /// conect our precious chart to the base layout
    void addChartToLayout();

    /// function that shows the abcissa as a black line.
    /// It creates a new series, where first and last points are the "first_date" and the "last_date"
    /// and the y values are zeros
    void setAbscissa();

};

#endif // GRAPHMANAGER_H
