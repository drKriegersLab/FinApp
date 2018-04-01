#include "tablemanager.h"
#include "finapp.h"
#include "ui_finapp.h"
/*
TableManager::TableManager(string filename) {
    DbManager = new DatabaseManager(100000, filename);
    collectRecords();
    cout<<"[TableManager] : " << records[0].change << endl;
}
*/

TableManager::TableManager(DatabaseManager *DataBaseMan) {
    DbManager = DataBaseMan;
    collectRecords();
}

void TableManager::collectRecords(){
    DbManager->getAllTransactions(&records);
    num_of_records = DbManager->getNumOfTransactions();

}

int TableManager::getNumOfRecords() {
    return num_of_records;
}


QStringList TableManager::getLabels() {
    table_labels<<LABELS;
    return table_labels;
}

void TableManager::getTransactionRecord(int record_id, TransactionRecord* record) {
    //cout<<"[TableManager] : " << records[record_id].change << endl;
    *record = records[record_id];
}

void TableManager::initTable(QTabWidget* Table) {
    /*
    Table->setRowCount(num_of_records);
    Table->setColumnCount(NUM_OF_LABELS);
    Table->setHorizontalHeaderLabels(getLabels());
    */
}

/**
 *** FUNCTION FOR FINAPP CLASS. ***
 * **/

void FinApp::showTableAllTransactions() {

    // initialize the table
    int num_of_records = TableMng->getNumOfRecords();

    ui->tableWidget->setRowCount(num_of_records);
    ui->tableWidget->setColumnCount(NUM_OF_LABELS);
    ui->tableWidget->setHorizontalHeaderLabels(TableMng->getLabels());

    // iterate over each record and set the corresponding cells in the table
    TransactionRecord record;
    for (int cyc_record = 0; cyc_record < num_of_records; cyc_record++){
        // get the record
        TableMng->getTransactionRecord(cyc_record, &record);
        // set the cells
        //QTableWidgetItem CellObject = new QTableWidgetItem();
        //CellObject.setText(QString::number(record.change));
        QFont Font;
        Font.setPixelSize(11);
        ui->tableWidget->setFont(Font);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->setItem(cyc_record, LABEL_ID_CHANGE, new QTableWidgetItem(QString::number(record.change)));
        ui->tableWidget->setItem(cyc_record, LABEL_ID_BALANCE, new QTableWidgetItem(QString::number(record.balance)));
        ui->tableWidget->setItem(cyc_record, LABEL_ID_NOTE, new QTableWidgetItem(QString::fromStdString(record.note)));
    }

}
