#include "tablemanager.h"
#include "finapp.h"
#include "ui_finapp.h"
#include "QMessageBox"

QStringList TableManager::getLabels() {
    QStringList table_labels; // specific string object that contains all necessary table labels
    table_labels<<LABELS;
    return table_labels;
}

/**
 *** FUNCTION FOR FINAPP CLASS. ***
 * */
/*
 * Show the selected transactions in the table.TODO: it should be the only table creator function
 * */
void FinApp::showTableSelectedTransactions(vector<TransactionRecord> transactions) {
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(transactions.size());
    ui->tableWidget->setColumnCount(NUM_OF_LABELS);
    ui->tableWidget->setHorizontalHeaderLabels(TableManager::getLabels());

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


