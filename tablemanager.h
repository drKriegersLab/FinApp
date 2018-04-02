#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <QTableWidgetItem>
#include "xml_parser/parse_csv.h"
#include "xml_parser/database_manager.h"


// default label configuration
#define LABELS "date"<<"change"<<"balance"<<"note"
#define NUM_OF_LABELS 4
#define LABEL_ID_DATE 0
#define LABEL_ID_CHANGE 1
#define LABEL_ID_BALANCE 2
#define LABEL_ID_NOTE 3



/*
 * This class is the responsible for all background operations/calculations of tableWidget. It collects the data from the database and in the future it will create
 * all the necessary data for the tableWidget. The calculations, sortings will be here.
 * */

class TableManager
{


private:
    /* VARIABLES */
    //TransactionRecord* records; // dynamically sized container of all records
    DatabaseManager* DbManager; // object that manages all necessary database operation
    QStringList table_labels; // specific string object that contains all necessary table labels
    //int num_of_records;
    vector<TransactionRecord> records;

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
    //TableManager(string filename);

    /*
     * init function that creates a local pointer to to the main database and collect all data out of it
     * TODO: do more flexible, dynamic the data transfers, like in the graphmanager class.
     * */
    TableManager(DatabaseManager* DataBaseMan);

    /*
     * It gets the predefined labels in specific format
     * */
    QStringList getLabels();


    /*
     * This function gets back the <record_id>-th record in the TransactionRecord structure
     * */
    void getTransactionRecord(int record_id, TransactionRecord* record);

    void initTable(QTabWidget* tableWidget);

    vector<TransactionRecord> selectFilter(QString filter, vector<TransactionRecord> records_input);

    vector<TransactionRecord> getRecords();

};

#endif // TABLEMANAGER_H
