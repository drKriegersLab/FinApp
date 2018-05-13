#ifndef DATABASE_H
#define DATABASE_H

#include "xml_parser/csv_input.h"
#include "xml_parser/parse_csv.h"
#include "xml_parser/database_manager.h"
/*
struct TransactionRecord {
    bool flag_disp_debug_messages;
    float change;
    float balance;
    string currency;
    QDate *date;
    string note;
};
*/
#define STRING_SELECT_FIELD_INCOME "income"
#define STRING_SELECT_FIELD_EXPENDITURE "expenditure"
#define STRING_SELECT_FIELD_PAYPASS "paypass"
#define STRING_SELECT_FIELD_CASHOUT "cashout"

class DataBase
{
private:
    vector<TransactionRecord> transactions;
    bool flag_disp_debug_messages;

    void createDataBaseFromCsvFields();
    void dropDebugPrompt(string message);
    void dropDebugOK();

    /* this function modify the first/init  record's date to the one which is in the first record of the csv file
     * */
    void setFirstRecordDate();

public:
    /// create database from csv file with an init balance
    DataBase(float init_balance, string input_filename);
    /// create empty database
    DataBase();

    DataBase(vector<TransactionRecord> transactions_input);
    //void addNewCsvContentToDataBase();
    int getNumberOfTransactions();
    TransactionRecord getTransaction(int tr_id);
    vector<TransactionRecord> getAllTransactions();

    void negateTotalDataBase();
};

#endif // DATABASE_H
