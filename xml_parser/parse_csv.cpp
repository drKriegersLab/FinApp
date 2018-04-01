#include "parse_csv.h"
#include <sstream>
#include <typeinfo>
//#include <iostream>
//#include <string>

CSV_parser::CSV_parser(string lines[], int number_of_lines) {
    cout << "CSV parser initialization ... " << endl;
    csv_lines = lines;
    num_of_records = (size_t)number_of_lines;
    csvRecords = new CsvFields[num_of_records];
    cout << "CSV parser initialized " << endl;
}


int CSV_parser::parseFile() {
    vector<string> content;

    string str_date;
    string str_field;

    for (size_t cyc_record = 0; cyc_record < num_of_records; cyc_record++) {
        content = splitLine(csv_lines[cyc_record], ';');                    

        csvRecords[cyc_record].change = stoi(content[FIELD_CHANGE]);
        csvRecords[cyc_record].currency = content[FIELD_CURRENCY];

        str_date = content[FIELD_DATEOFTRANSACTION];
        csvRecords[cyc_record].date_of_transaction.yy = stoi(str_date.substr(0,4));
        csvRecords[cyc_record].date_of_transaction.mm = stoi(str_date.substr(4,2));
        csvRecords[cyc_record].date_of_transaction.dd = stoi(str_date.substr(6,2));

        str_date = content[FIELD_DATEOFREALIZATION];
        csvRecords[cyc_record].date_of_realization.yy = stoi(str_date.substr(0,4));
        csvRecords[cyc_record].date_of_realization.mm = stoi(str_date.substr(4,2));
        csvRecords[cyc_record].date_of_realization.dd = stoi(str_date.substr(6,2));

        csvRecords[cyc_record].note = content[FIELD_NOTE1];
        for (int cyc_field = FIELD_NOTE2; cyc_field < content.size(); cyc_field++) {
            csvRecords[cyc_record].note += content[cyc_field];
        }


    }
    /*
    listAllItems(FIELD_CHANGE);
    listAllItems(FIELD_CURRENCY);c
    //listAllItems(FIELD_DATEOFTRANSACTION);
    //listAllItems(FIELD_DATEOFREALIZATION);
    listAllItems(FIELD_TRANSACTIONNAME);
    listAllItems(FIELD_FROMPARTNERID);
    listAllItems(FIELD_FROMPARTNERNAME);
    listAllItems(FIELD_TRANSACTIONTYPE);

    listAllItems(-1);
    */

    /*
    for (int line_num = 0; line_num < num_of_records; line_num++){
        cout << line_num << " : " << csv_lines[line_num] << endl;
    }
    */


    printf("parsing finished\n");

    return 0;
}

vector<string> CSV_parser::splitLine(string line, char deliminiter) {
    istringstream tokenStream(line);
    vector<string> pieces;
    string token;

    while(getline(tokenStream, token, deliminiter)) {
        pieces.push_back(token);
    }
    return pieces;


}

void CSV_parser::listAllItems(int item_id) {

    switch (item_id) {
        case FIELD_CHANGE:{
            printf("all changes in the examined database:\n");
            for (size_t i = 0; i < num_of_records; i++) {
                cout << i << " : " << csvRecords[i].change << endl;
            }
            break;
        }
        case FIELD_CURRENCY: {
            printf("all currencies in the examined database:\n");
            for (size_t i = 0; i < num_of_records; i++) {
                cout << i << " : " << csvRecords[i].currency << endl;
            }
            break;
        }
        default: {
            printf("**** list of  all transactions ****\n");
            for (size_t i = 0; i < num_of_records; i++) {
                cout << i << "-th transaction:" << endl;
                cout << " change:              " << csvRecords[i].change << endl;
                cout << " currency:            " << csvRecords[i].currency << endl;
                cout << " note:                " << csvRecords[i].note << endl;
                //cout << " date of transaction: " << csvRecords[i].date_of_transaction << endl;
                //cout << " date of realization: " << csvRecords[i].date_of_realization << endl;
                //cout << " transaction name:    " << csvRecords[i].transaction_name << endl;
                //cout << " from partner (id):   " << csvRecords[i].from_partner_id << endl;
                //cout << " from partner (name): " << csvRecords[i].from_partner_name << endl;
            }
            break;
        }
    } // end of switch-case structure

}

int CSV_parser::getCsvRecords(CsvFields *records[]) {
    *records = csvRecords;
    return 0;
}
