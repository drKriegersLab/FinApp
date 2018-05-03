#include "tablemanager.h"
#include "finapp.h"
#include "ui_finapp.h"
#include "QMessageBox"
#include <sstream>
#include <iostream>
#include <array>

QStringList TableManager::getLabels() {
    QStringList table_labels; // specific string object that contains all necessary table labels
    table_labels<<LABELS;
    return table_labels;
}

int TableManager::getMaxElementOfArray(int* input_array, size_t size) {
    int max_element = input_array[0];

    for (int cyc_element = 1; cyc_element < size; cyc_element++ ) {
        if (input_array[cyc_element] > max_element) {
            max_element = input_array[cyc_element];
        }
    }

    return max_element;
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


    // temporaly containers of displayed strings
    QString displayed_date;
    QString displayed_change;
    QString displayed_balance;
    QString displayed_note;

    // font setup
    QFont Font;
    Font.setPixelSize(11);

    // fill the table
    for (int cyc_rec = 0; cyc_rec < transactions.size(); cyc_rec++) {

        ui->tableWidget->setFont(Font);
        //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        //ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        // DATE
        displayed_date = transactions[cyc_rec].date ->toString("yyyy.MM.dd");
        ui->tableWidget->setItem(cyc_rec, LABEL_ID_DATE, new QTableWidgetItem(displayed_date));

        // CHANGE
        displayed_change = QString::number(transactions[cyc_rec].change);
        ui->tableWidget->setItem(cyc_rec, LABEL_ID_CHANGE, new QTableWidgetItem(displayed_change));

        // BALANCE
        displayed_balance = QString::number(transactions[cyc_rec].balance);
        ui->tableWidget->setItem(cyc_rec, LABEL_ID_BALANCE, new QTableWidgetItem(displayed_balance));

        // NOTE
        displayed_note = QString::fromStdString(transactions[cyc_rec].note);
        ui->tableWidget->setItem(cyc_rec, LABEL_ID_NOTE, new QTableWidgetItem(displayed_note));
    }

    // set rows height to be fixed
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(24);

    // allow the user able to modify the columns' sizes
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(LABEL_ID_CHANGE, QHeaderView::Interactive);
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(LABEL_ID_BALANCE, QHeaderView::Interactive);
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(LABEL_ID_NOTE, QHeaderView::Interactive);

}




