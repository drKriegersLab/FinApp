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

    /****  PRIVATE VARIABLE DEFINITIONS ****/

    size_t num_of_records = 0; // only the initDB appendNewRecords funtions should be used it
    TransactionRecord *transactions = {}; // dinamically sized databse container (used this formula, because it is maybe more flexible, when I want to include more than one elements)

    /**** PRIVATE FUNCTION DEFINITIONS ****/

    /*
     * function for sotring csv records to the database
     * */
    int createDBFromCsvFields();

    /*
     * function for reseting and initializing the databse with a first balance
     * The start point of the database will be 2016.01.01
     * */
    int initDB(float init_balance);

    /*
     * function for appending new database parts to the common database
     * */
    int appendNewRecords(TransactionRecord records[], size_t num_of_new_records);

    /*
     * function for quick, identified and clear debug prompts
     * */
    void dropDebugPrompt(string prompt);

public:
    /**** PUBLIC FUNCTION DEFINITIONS ****/

    /*
     * init function that initialize the DB only with the first balance
     * */
    DatabaseManager(float init_balance);

    /*
     * init function that initialize the DB with the first balance and creates the first records
     * from a csv parsing results
     * */
    DatabaseManager(float init_balance, CsvFields csvContent[], size_t num_of_lines);

    /*
     * init function that do all necessary steps from reading CSV file to creating database
    */
    DatabaseManager(float init_balance, string filename);

    /*
     * function for creating new records from csv content
     * */
    int addCsvToDB(CsvFields csvContent[], size_t num_of_lines);

    /*
     * get functions
     * */
    void getTransaction(int record_id, TransactionRecord* record);

    int getNumOfTransactions();

    void getAllTransactions(TransactionRecord* records[]);

    int getAllChangesWDate(int* changes[], DateStruct* dates[]);

    int getAllCurrenciesWDate(string* currs[], DateStruct* dates[]);

    int getAllTransDates(DateStruct* dates[]);

    int getAllTransNamesWDates(string* names[], DateStruct* dates[]);

    int getAllTransTypesWDates(string* types[], DateStruct* dates[]);

   /*
    * print each record
    * */
    void printAllTransactions();

    /*
     * SELECT FUNCTIONS
     * */
    vector<TransactionRecord> selectIncomes(vector<TransactionRecord> records_input);
    vector<TransactionRecord> selectExpenditures(vector<TransactionRecord> records_input);
    vector<TransactionRecord> selectPpassPayments(vector<TransactionRecord> records_input);
    vector<TransactionRecord> selectCashouts(vector<TransactionRecord> records_input);



};

#endif // DATABASE_MANAGER_H
