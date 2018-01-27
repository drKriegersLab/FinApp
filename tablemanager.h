#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <QTableWidgetItem>
#include "xml_parser/parse_csv.h"
#include "xml_parser/database_manager.h"


// default label configuration
#define LABELS "change"<<"balance"<<"tr_name"<<"partner_id"<<"tr_type"
#define NUM_OF_LABELS 5
#define LABEL_CHANGE 0
#define LABEL_BALANCE 1
#define LABEL_TR_NAME 2
#define LABEL_PARTNER_ID 3
#define LABEL_TR_TYPE 4

/*
 * This class is the responsible for all background operations/calculations of tableWidget. It collects the data from the database and in the future it will create
 * all the necessary data for the tableWidget. The calculations, sortings will be here.
 * */

class TableManager
{


private:
    /* VARIABLES */
    TransactionRecord* records; // dynamically sized container of all records
    DatabaseManager* DbManager; // object that manages all necessary database operation
    QStringList table_labels; // specific string object that contains all necessary table labels
    int num_of_records;

    /* FUNCTIONS */
    /*
     * It gets the record information from database manager
     * */
    void collectRecords();


public:
    /* VARIABLES */
    int getNumOfRecords();

    /* FUNCTIONS */

    /*
     * It initializates the database manager with the specified csv file and gets the records from it
     * */
    TableManager(string filename);

    /*
     * It gets the predefined labels in specific format
     * */
    QStringList getLabels();


    /*
     * This function gets back the <record_id>-th record in the TransactionRecord structure
     * */
    void getTransactionRecord(int record_id, TransactionRecord* record);

};

#endif // TABLEMANAGER_H
