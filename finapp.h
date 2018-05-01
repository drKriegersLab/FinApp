#ifndef FINAPP_H
#define FINAPP_H

#include <QMainWindow>
#include "tablemanager.h"
#include "graphmanager.h"
#include "xml_parser/database_manager.h"
#include <QComboBox>
#include "database.h"
#include <QtCharts/QChartView>
#include <QGridLayout>
#include <QtWidgets/QCheckBox>
#include <QColor>
#include <QPushButton>


namespace Ui {
class FinApp;
}

class FinApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit FinApp(QWidget *parent = 0);

    void getUi(FinApp &user_interface);



    ~FinApp();

private slots:
    void on_actionOpen_triggered();

    //void on_asdLineEdit_editingFinished();

    //void on_comboBox_currentTextChanged(const QString &current_text);

    void on_filterSelector_currentTextChanged(const QString &current_text);

    /*
     * Handler function of FilterReset button. It makes unvisible the filterSelectors, delete the vector of selected items,
     * and set the first one's field to default.
     * */
    void on_buttonFilterReset_released();


    //void on_checkBox_clicked(bool checked);
    void checkBoxStateChanged_all(int status);
    void checkBoxStateChanged_income(int status);
    void checkBoxStateChanged_expenditure(int status);
    void checkBoxStateChanged_exp_all(int status);
    void checkBoxStateChanged_exp_paypass(int status);
    void checkBoxStateChanged_exp_cashout(int status);

    /* curve color changer functions */
    void on_buttonColor_all_released();

    void on_buttonColor_income_released();

    void on_buttonColor_exp_all_released();

    void on_buttonColor_exp_ppass_released();

    void on_buttonColor_exp_cashout_released();

private:

    /* VARIABLES */
    // declaration of ui, main database, main graph manager objects
    Ui::FinApp *ui;
    DataBase *DbFull;
    GraphManager *Graph;

    // declarations regarding chart
    QtCharts::QChartView *chartView;
    QGridLayout* ChartLayout;

    // table's filter selector variables
    int filter_selector_counter = 0;
    QString default_item;
    vector<QString> filter_items;
    vector<QString> filter_selected_items;

    // relevant transaction lists, those should be stored
    vector<TransactionRecord> full_database;
    vector<TransactionRecord> filtered_database;

    // list of main checkboxes: This vector stores all checkboxes' pointers in the graph selector
    // of which only one can be selected at the same time
    vector<QCheckBox*> main_checkboxes;

    // relevant series
    QtCharts::QLineSeries* series_all_transactions;
    QtCharts::QLineSeries* series_incomes;
    QtCharts::QLineSeries* series_expenditures_all;
    QtCharts::QLineSeries* series_expenditures_cashout;
    QtCharts::QLineSeries* series_expenditures_ppass;

    /* FUNCTIONS */

    void dropDebugPrompt(string message);
    void showTableAllTransactions();

    void showTableSelectedTransactions(vector<TransactionRecord> transactions);

    /*
     * store to comboboxe's lists elemets from specified filter items those are not selected yet
     * */
    void setFilterSelectorItems(QComboBox *comboBox);

    /// init function for all graph-related objects
    void initGraphView();

    /// implementation of exclusive checkbox selection
    void resetOtherMainCheckBoxes(QString except_checkbox_name);

    /// set the bacground color of the given button to the given color
    void setButtonColor(QPushButton* button, QColor color);

    void setCurveColor(QPushButton* button, QtCharts::QLineSeries* series);



};

#endif // FINAPP_H
