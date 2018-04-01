#ifndef FINAPP_H
#define FINAPP_H

#include <QMainWindow>
#include "tablemanager.h"
#include "graphmanager.h"
#include <QComboBox>

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

    void on_filterSelector1_currentTextChanged(const QString &arg1);

    void on_filterSelector2_currentTextChanged(const QString &arg1);

    void on_filterSelector3_currentTextChanged(const QString &arg1);

private:
    Ui::FinApp *ui;
    TableManager *TableMng;
    DatabaseManager *DbMng;
    GraphManager *GraphMng;

    int filter_selector_counter = 0;
    QString default_item;
    vector<QString> filter_items;
    vector<QString> filter_selected_items;

    void dropDebugPrompt(string message);
    void showTableAllTransactions();
    void showGraphAllTransactions();

    /*
     * store to comboboxe's lists elemets from specified filter items those are not selected yet
     * */
    void setFilterSelectorItems(QComboBox *comboBox);

};

#endif // FINAPP_H
