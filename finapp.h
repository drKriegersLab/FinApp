#ifndef FINAPP_H
#define FINAPP_H

#include <QMainWindow>

namespace Ui {
class FinApp;
}

class FinApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit FinApp(QWidget *parent = 0);
    ~FinApp();

private:
    Ui::FinApp *ui;
};

#endif // FINAPP_H
