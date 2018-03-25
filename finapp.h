#ifndef FINAPP_H
#define FINAPP_H

#include <QMainWindow>
#include "tablemanager.h"
#include "graphmanager.h"

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

private:
    Ui::FinApp *ui;
    TableManager *TableMng;
    DatabaseManager *DbMng;
    GraphManager *GraphMng;

    void dropDebugPrompt(string message);
    void showTableAllTransactions();
    void showGraphAllTransactions();

};

#endif // FINAPP_H
