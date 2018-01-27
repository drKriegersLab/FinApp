#include "finapp.h"
#include "ui_finapp.h"
#include <QTableWidgetItem>
#include "tablemanager.h"

FinApp::FinApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinApp)
{
    ui->setupUi(this);
    string filename = "/home/drkrieger/01_PetProjects/FinApp/xml_base/2017_01.csv";
    TableDbManager = new TableManager(filename);
}

FinApp::~FinApp()
{
    delete ui;
}

void FinApp::on_actionOpen_triggered()
{
    /* TEMPLATE
    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setColumnCount(3);
    QStringList label_list;
    label_list<<"A"<<"B"<<"C";
    ui->tableWidget->setHorizontalHeaderLabels(label_list);
    ui->tableWidget->setItem(1,1, new QTableWidgetItem(QString::number(12)));
    */

    // initialize the table
    int num_of_records = TableDbManager->getNumOfRecords();
    ui->tableWidget->setRowCount(num_of_records);
    ui->tableWidget->setColumnCount(NUM_OF_LABELS);
    ui->tableWidget->setHorizontalHeaderLabels(TableDbManager->getLabels());

    // iterate over each record and set the corresponding cells in the table
    TransactionRecord record;
    for (int cyc_record = 0; cyc_record < num_of_records; cyc_record++){
        // get the record
        TableDbManager->getTransactionRecord(cyc_record, &record);
        // set the cells
        ui->tableWidget->setItem(cyc_record, LABEL_CHANGE, new QTableWidgetItem(QString::number(record.change)));
        ui->tableWidget->setItem(cyc_record, LABEL_BALANCE, new QTableWidgetItem(QString::number(record.balance)));
        ui->tableWidget->setItem(cyc_record, LABEL_TR_NAME, new QTableWidgetItem(QString::fromStdString(record.tr_name)));
        ui->tableWidget->setItem(cyc_record, LABEL_PARTNER_ID, new QTableWidgetItem(QString::fromStdString(record.partner_id)));
        ui->tableWidget->setItem(cyc_record, LABEL_TR_TYPE, new QTableWidgetItem(QString::fromStdString(record.tr_type)));
    }




}

/*
 * DEBUG PROMPTS
 * */
void FinApp::dropDebugPrompt(string message) {
    cout << "[FinApp] : " << message << endl;
}
