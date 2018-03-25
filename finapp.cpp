#include "finapp.h"
#include "ui_finapp.h"
#include <QFileDialog>
//#include <QTableWidgetItem>
//#include <QFont>
//#include <QtWidgets/QApplication>
//#include <QtWidgets/QMainWindow>
//#include <QtCharts/QChartView>
//#include <QtCharts/QLineSeries>
//#include <QtCharts/QScatterSeries>
//#include <QtCharts/QValueAxis>
//#include <QtCharts/QLogValueAxis>
//#include <QtWidgets/QLabel>

//#include "tablemanager.h"

FinApp::FinApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinApp)
{
    ui->setupUi(this);
    //string filename = "/home/drkrieger/01_PetProjects/FinApp/xml_base/2017_01.csv";
    //TableDbManager = new TableManager(filename);

}

FinApp::~FinApp()
{
    delete ui;
}

void FinApp::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open source file", "/home/drkrieger/01_PetProjects/FinApp/xml_base/", "CSV files (*.csv)");

    DbMng = new DatabaseManager(100000, filename.toStdString());
    TableMng = new TableManager(DbMng);
    GraphMng = new GraphManager(DbMng);

    showTableAllTransactions();
    showGraphAllTransactions();

}

/*
 * DEBUG PROMPTS
 * */
void FinApp::dropDebugPrompt(string message) {
    cout << "[FinApp] : " << message << endl;
}

