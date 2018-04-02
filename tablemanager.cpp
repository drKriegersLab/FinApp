#include "tablemanager.h"
#include "finapp.h"
#include "ui_finapp.h"
#include "QMessageBox"
/*
TableManager::TableManager(string filename) {
    DbManager = new DatabaseManager(100000, filename);
    collectRecords();
    cout<<"[TableManager] : " << records[0].change << endl;
}
*/

TableManager::TableManager(DatabaseManager *DataBaseMan) {
    DbManager = DataBaseMan;
    //database_filters.push_back();

    collectRecords();
}

void TableManager::collectRecords(){
    TransactionRecord* records_array;
    DbManager->getAllTransactions(&records_array);

    for (int cyc_rec = 0; cyc_rec < DbManager->getNumOfTransactions(); cyc_rec++) {
        records.push_back(records_array[cyc_rec]);
    }

}

int TableManager::getNumOfRecords() {
    return records.size();
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

vector<TransactionRecord> TableManager::selectFilter(QString filter, vector<TransactionRecord> records_input){
    vector<TransactionRecord> records_output;

    if (filter == "income") {
        records_output = DbManager->selectIncomes(records_input);
    }
    else if ( filter == "expenditure" ) {
        records_output = records_input;
        //records_output = DbManager->selectExpenditures(records_input);
    }
    else if ( filter ==  "paypass" ) {
        records_output = records_input;
        //records_output = DbManager->selectPpassPayments(records_input);
    }
    else if ( filter == "chashout" ) {
        records_output = records_input;
        //records_output = DbManager->selectCashouts(records_input);
    }
    else {
        //QMessageBox::information(, "filter not correct", "filter is not iplemented yet :-(");
        records_output = records_input;
    }

    return records_output;
}

vector<TransactionRecord> TableManager::getRecords(){
    return records;
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
        ui->tableWidget->setItem(cyc_record, LABEL_ID_DATE, new QTableWidgetItem(record.date->toString("yyyy.MM.dd")));
        ui->tableWidget->setItem(cyc_record, LABEL_ID_CHANGE, new QTableWidgetItem(QString::number(record.change)));
        ui->tableWidget->setItem(cyc_record, LABEL_ID_BALANCE, new QTableWidgetItem(QString::number(record.balance)));
        ui->tableWidget->setItem(cyc_record, LABEL_ID_NOTE, new QTableWidgetItem(QString::fromStdString(record.note)));
    }

}

/*
 * Show only the selected transactions in the table.TODO: it should be the only table creator function
 * */
void FinApp::showTableSelectedTransactions(vector<TransactionRecord> transactions) {
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(transactions.size());
    ui->tableWidget->setColumnCount(NUM_OF_LABELS);
    ui->tableWidget->setHorizontalHeaderLabels(TableMng->getLabels());

    for (int cyc_rec = 0; cyc_rec < transactions.size(); cyc_rec++) {
        QFont Font;
        Font.setPixelSize(11);
        ui->tableWidget->setFont(Font);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->setItem(cyc_rec, LABEL_ID_DATE, new QTableWidgetItem(transactions[cyc_rec].date ->toString("yyyy.MM.dd")));
        ui->tableWidget->setItem(cyc_rec, LABEL_ID_CHANGE, new QTableWidgetItem(QString::number(transactions[cyc_rec].change)));
        ui->tableWidget->setItem(cyc_rec, LABEL_ID_BALANCE, new QTableWidgetItem(QString::number(transactions[cyc_rec].balance)));
        ui->tableWidget->setItem(cyc_rec, LABEL_ID_NOTE, new QTableWidgetItem(QString::fromStdString(transactions[cyc_rec].note)));
    }
}


