#include "finapp.h"
#include "ui_finapp.h"

FinApp::FinApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinApp)
{
    ui->setupUi(this);
}

FinApp::~FinApp()
{
    delete ui;
}
