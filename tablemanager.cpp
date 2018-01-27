#include "tablemanager.h"
#include "finapp.h"
#include "ui_finapp.h"

TableManager::TableManager(string filename) {
    DbManager = new DatabaseManager(100000, filename);
    collectRecords();
    cout<<"[TableManager] : " << records[0].change << endl;
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
    cout<<"[TableManager] : " << records[record_id].change << endl;
    *record = records[record_id];
}
