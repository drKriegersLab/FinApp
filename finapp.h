#ifndef FINAPP_H
#define FINAPP_H

#include <QMainWindow>
#include "tablemanager.h"

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
    TableManager *TableDbManager;

    void dropDebugPrompt(string message);

};

#endif // FINAPP_H
