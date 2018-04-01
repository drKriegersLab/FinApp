#ifndef PARSE_CSV_H
#define PARSE_CSV_H



#include "xml_parser_main.h"
#include "csv_input.h"

#define MAXNUMOFRECORDS CSVMAXLINES

#define MAXNUMOFFIELDS 13

#define FIELD_ACCOUNTID 0
#define FIELD_IN_OR_OUT 1
#define FIELD_CHANGE 2
#define FIELD_CURRENCY 3
#define FIELD_DATEOFTRANSACTION 4
#define FIELD_DATEOFREALIZATION 5
#define FIELD_NEWBALANCE 6
#define FIELD_NOTE1 7
#define FIELD_NOTE2 8
#define FIELD_NOTE3 9
#define FIELD_NOTE4 10
#define FIELD_NOTE5 11
#define FIELD_NOTE6 12


struct DateStruct {
    int yy;
    int mm;
    int dd;
};

struct CsvFields {
    int id;
    int inout;
    int change;
    string currency;
    DateStruct date_of_transaction;
    DateStruct date_of_realization;
    int new_balance;
    string note;
};


/******
 * This class is for reading and analysing the CSV file content and if it is able to
 * recognize it, parsing all fields and store it into a structure. The desired fields are
 * defined in the CsvFields structure, and the fields' places  in the CSV filem are defined
 *  with FIELD_xxx constants
 * ****/
class CSV_parser {
    size_t num_of_records; // number of valid transactions in the csv
    string *csv_lines; //string array of csv content
    CsvFields *csvRecords = {}; //parsed csv content sorted into records

public:
    /*
     * init function.
     * prepare the initial state for parsing.
     * in:
     *      lines: the read lines from the csv
     *      number_of_lines: the valid number of records
    */
    CSV_parser(string lines[], int number_of_lines);

    /*
     * function for parsing csv file line by line and store the results into the csvRecords structure array
     * */
    int parseFile();

    int getCsvRecords(CsvFields* records[]);

private:
    /*
     * tool for splitting strings to pieces, if there are specified
     * deliminiter between the fields
     * in:
     *      line: the line what will be splitted
     *      deliminiter: the deliminiter character
     * out: vector<string>: the array of each fields
     * */
    vector<string> splitLine(string line, char deliminiter);

    /*
     * function for displaying all results (for debug)
     * in:
     *      item_id: you can specify, what item do you want to see.
     *              if you give invalid number, it will print all fields of each transaction(default case)
     * */
    void listAllItems(int item_id);



};

#endif // PARSE_CSV_H
