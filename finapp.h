#ifndef FINAPP_H
#define FINAPP_H

#include <QMainWindow>
#include "tablemanager.h"
#include "graphmanager.h"
#include "xml_parser/database_manager.h"
#include <QComboBox>
#include "database.h"

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


private:
    Ui::FinApp *ui;
    //TableManager *TableMng;
    //DatabaseManager *DbMng;
    DataBase *DbFull;
    GraphManager *GraphMng;

    int filter_selector_counter = 0;
    QString default_item;
    vector<QString> filter_items;
    vector<QString> filter_selected_items;

    vector<TransactionRecord> full_database;
    vector<TransactionRecord> filtered_database;

    void dropDebugPrompt(string message);
    void showTableAllTransactions();
    void showGraphSelectedTransactions(vector<TransactionRecord> transactions);
    void showTableSelectedTransactions(vector<TransactionRecord> transactions);

    /*
     * store to comboboxe's lists elemets from specified filter items those are not selected yet
     * */
    void setFilterSelectorItems(QComboBox *comboBox);

};

#endif // FINAPP_H
