#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "parse_csv.h"
#include "csv_input.h"
#include "parse_csv.h"
#include "iostream"
#include <QDate>

struct TransactionRecord {
    float change;
    float balance;
    string currency;
    QDate *date;
    string note;
    /*string tr_name;
    string partner_id;
    string partner_name;
    string tr_type;
    string tr_note;
    */
};

/*
 * This class manages all database-level operations/calculations like creating the database and other services. It operates as an interface between the file-level
 * and higher-level (for ecample table manipulations, other calculations, sorting) operations too.
 * */
class DatabaseManager {
private:
    void dropDebugPrompt(string prompt);

public:
    /*
     * Function for managing the application of selected filters. It tells us, what function we need to call for do
     * the desired process
     * */
    static vector<TransactionRecord> selectFilter(QString filter, vector<TransactionRecord> records_input);

    /*
     * SELECT FUNCTIONS
     * */
    static vector<TransactionRecord> selectIncomes(vector<TransactionRecord> records_input);
    static vector<TransactionRecord> selectExpenditures(vector<TransactionRecord> records_input);
    static vector<TransactionRecord> selectPpassPayments(vector<TransactionRecord> records_input);
    static vector<TransactionRecord> selectCashouts(vector<TransactionRecord> records_input);



};

#endif // DATABASE_MANAGER_H
