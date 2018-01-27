#include "parse_csv.h"
#include <sstream>
#include <typeinfo>

CSV_parser::CSV_parser(string lines[], int number_of_lines) {
    printf("CSV parser initialization ...\n");
    csv_lines = lines;
    num_of_records = (size_t)number_of_lines;
    csvRecords = new CsvFields[num_of_records];
    printf("CSV parser initialized\n");
}


int CSV_parser::parseFile() {
    vector<string> content;

    for (size_t cyc_record = 0; cyc_record < num_of_records; cyc_record++) {
        content = splitLine(csv_lines[cyc_record], ';');

        csvRecords[cyc_record].change = stoi(content[FIELD_CHANGE]);
        csvRecords[cyc_record].currency = content[FIELD_CURRENCY];
        //csvRecords[cyc_record].date_of_transaction = content[FIELD_DATEOFTRANSACTION];
        //csvRecords[cyc_record].date_of_realization = content[FIELD_DATEOFREALIZATION];
        csvRecords[cyc_record].transaction_name = content[FIELD_TRANSACTIONNAME];
        csvRecords[cyc_record].from_partner_id = content[FIELD_FROMPARTNERID];
        csvRecords[cyc_record].from_partner_name = content[FIELD_FROMPARTNERNAME];
        csvRecords[cyc_record].transaction_type = content[FIELD_TRANSACTIONTYPE];
    }
    /*
    listAllItems(FIELD_CHANGE);
    listAllItems(FIELD_CURRENCY);
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
        /*
        case FIELD_DATEOFTRANSACTION: {
            printf("all dates of transactions in the examined database:\n");
            for (size_t i = 0; i < num_of_records; i++) {
                cout << i << " : " << csvRecords[i].date_of_transaction << endl;
            }
            break;
        }

        case FIELD_DATEOFREALIZATION: {
            printf("all transactions' realization date in the examined database:\n");
            for (size_t i = 0; i < num_of_records; i++) {
                cout << i << " : " << csvRecords[i].date_of_realization << endl;
            }
            break;
        }
        */
        case FIELD_TRANSACTIONNAME: {
            printf("all transaction names in the  examined database:\n");
            for (size_t i = 0; i < num_of_records; i++) {
                cout << i << " : " << csvRecords[i].transaction_name << endl;
            }
            break;
        }
        case FIELD_FROMPARTNERID: {
            printf("all partner ids of partners those are from intake in the examined database:\n");
            for (size_t i = 0; i < num_of_records; i++) {
                cout << i << " : " << csvRecords[i].from_partner_id << endl;
            }
            break;
        }
        case FIELD_FROMPARTNERNAME: {
            printf("all names of partners those are from intake in the examined database:\n");
            for (size_t i = 0; i < num_of_records; i++) {
                cout << i << " : " << csvRecords[i].from_partner_name << endl;
            }
            break;
        }
        default: {
            printf("**** list of  all transactions ****\n");
            for (size_t i = 0; i < num_of_records; i++) {
                cout << i << "-th transaction:" << endl;
                cout << " change:              " << csvRecords[i].change << endl;
                cout << " currency:            " << csvRecords[i].currency << endl;
                //cout << " date of transaction: " << csvRecords[i].date_of_transaction << endl;
                //cout << " date of realization: " << csvRecords[i].date_of_realization << endl;
                cout << " transaction name:    " << csvRecords[i].transaction_name << endl;
                cout << " from partner (id):   " << csvRecords[i].from_partner_id << endl;
                cout << " from partner (name): " << csvRecords[i].from_partner_name << endl;
            }
            break;
        }
    } // end of switch-case structure

}

int CSV_parser::getCsvRecords(CsvFields *records[]) {
    *records = csvRecords;
    return 0;
}
