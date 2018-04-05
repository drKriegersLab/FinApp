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

class DataBase
{
private:
    vector<TransactionRecord> transactions;
    bool flag_disp_debug_messages;

    void createDataBaseFromCsvFields();
    void dropDebugPrompt(string message);
    void dropDebugOK();

public:
    DataBase(float init_balance, string input_filename);
    DataBase();
    //void addNewCsvContentToDataBase();
    int getNumberOfTransactions();
    TransactionRecord getTransaction(int tr_id);
    vector<TransactionRecord> getAllTransactions();
};

#endif // DATABASE_H
