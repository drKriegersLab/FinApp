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
#include "tools.h"

/*
 * This class responsible for all graph management and manipulation tasks
 * */
class GraphManager
{
public:
    ///init function for creating a totally new chart from the given records
    GraphManager(QGridLayout* Layout, vector<TransactionRecord> records, string title);

    /// init without series
    GraphManager(QGridLayout *Layout, string title);

    /// function for insert new data series
    QtCharts::QLineSeries* addSeries(vector<TransactionRecord> records);


    /// function for set upt the title of the figure
    void setTitle(string title);

    QtCharts::QLineSeries* getFirstSeries();

    /// function for delete the base series
    void deleteFirstSeries();

    /// function for remove all series from the graph manager
    void deleteAllSeries();

    /// function for remove a selected series. If it is not existing, it drops a warning to the console only.
    void deleteSeries(QtCharts::QLineSeries* series);

    /// static function for creating a totaly new chart separately from the base class
    static void createGraphChartView(QGridLayout* Layout, vector<TransactionRecord> records, string title);         


private:

    /* VARIABLES */

    // basic objects
    QGridLayout* ParentLayout; // base layout, where we the object's class is
    QtCharts::QLineSeries* Series; // data series
    QtCharts::QChart* Chart; // chart's object
    QtCharts::QChartView* ChartView; // chart's view object

    // axis objects
    QtCharts::QDateTimeAxis *axisX;
    QtCharts::QValueAxis *axisY;

    // variables for automatic range adjusting of axes
    int minval_axis_y = 0;
    int maxval_axis_y = 0;

    QDateTime first_date;
    QDateTime last_date;

    QtCharts::QLineSeries* first_series;

    int num_of_series;
    vector<QtCharts::QLineSeries*> series_container; // series in the graph manager

    /* PRIVATE FUNCTIONS */

    /// conect our precious chart to the base layout
    void addChartToLayout();

    /// function that shows the abcissa as a black line.
    /// It creates a new series, where first and last points are the "first_date" and the "last_date"
    /// and the y values are zeros
    void setAbscissa();

    /// implementation of autorange. Each time, when you call this function, it checks all stored Series
    /// in the collection, and determines the necessary maximum and minimum of the Y axis.
    void updateOrdinateRange();

    /// Drop class specific debug message to the Console.
    void dropDebugPrompt(string message);

};

#endif // GRAPHMANAGER_H
