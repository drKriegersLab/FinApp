#include "database.h"
#include <sstream>

DataBase::DataBase() {
    dropDebugPrompt("initialize empty database");
    dropDebugOK();
}


DataBase::DataBase(float init_balance, string input_filename)
{
    flag_disp_debug_messages = true;
    string *csv_lines;
    int num_of_csv_lines;

    // init database
    TransactionRecord record_tmp; // = new TransactionRecord();
    record_tmp.change = init_balance;
    record_tmp.balance = init_balance;
    record_tmp.currency = "HUF";
    record_tmp.date = new QDate(2017,1,1);
    record_tmp.note = "init balance";

    transactions.push_back(record_tmp);

    // read csv
    dropDebugPrompt("read csv file");
    CSV_reader Reader(input_filename);
    Reader.readFile();
    Reader.getNumOfLines(&num_of_csv_lines);
    Reader.getLines(&csv_lines);
    dropDebugOK();

    // parsing its content
    dropDebugPrompt("parse csv content");
    CSV_parser Parser(csv_lines, num_of_csv_lines);
    Parser.parseFile();
    CsvFields *csv_content;
    Parser.getCsvRecords(&csv_content);
    dropDebugOK();

    // store csv records to transaction temp database
    for (size_t rec_id = 0; rec_id < num_of_csv_lines; rec_id ++) {

        record_tmp.change = (float)csv_content[rec_id].change;
        record_tmp.balance = transactions.back().balance + csv_content[rec_id].change;
        record_tmp.currency = csv_content[rec_id].currency;
        record_tmp.date = new QDate(csv_content[rec_id].date_of_realization.yy, csv_content[rec_id].date_of_realization.mm, csv_content[rec_id].date_of_realization.dd);
        record_tmp.note = csv_content[rec_id].note;

        transactions.push_back(record_tmp);
    }

    setFirstRecordDate();
    dropDebugOK();
}

DataBase::DataBase(vector<TransactionRecord> transaction_input) {
    flag_disp_debug_messages = true;

    dropDebugPrompt("init database\n");
    float balance = 0;
    TransactionRecord record_temp;

    for (int cyc_transaction = 0; cyc_transaction < transaction_input.size(); cyc_transaction++) {
        record_temp = transaction_input[cyc_transaction];
        balance += record_temp.change;
        record_temp.balance = balance;
        cout << "bal: " << record_temp.balance << endl;

        transactions.push_back(record_temp);
    }
    dropDebugOK();
}

void DataBase::negateTotalDataBase() {
    dropDebugPrompt("negate total databse .. ");
    float balance = 0;
    vector<TransactionRecord> transactions_temp = transactions;
    transactions.erase(transactions.begin(), transactions.end());
    TransactionRecord record_temp;

    for (int cyc_transaction = 0; cyc_transaction < transactions_temp.size(); cyc_transaction++) {
        record_temp = transactions_temp[cyc_transaction];
        balance -= record_temp.change;
        record_temp.balance = balance;

        transactions.push_back(record_temp);
    }
    dropDebugOK();
}

int DataBase::getNumberOfTransactions() {
    return transactions.size();
}

TransactionRecord DataBase::getTransaction(int tr_id) {
    return transactions[tr_id];
}

vector<TransactionRecord> DataBase::getAllTransactions() {
    return transactions;
}

void DataBase::setFirstRecordDate(){
    if (transactions.size() > 1) {
        transactions[0].date = transactions[1].date;
    }
}

void DataBase::dropDebugPrompt(string message) {
    if (flag_disp_debug_messages) {
        cout << "[DataBase] : " << message << " ... ";
    }
}

void DataBase::dropDebugOK() {
    if (flag_disp_debug_messages) {
        cout << "\t[OK]" << endl;
    }
}


