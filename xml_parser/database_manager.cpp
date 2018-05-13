#include "xml_parser_main.h"
#include "database_manager.h"
#include "database.h"

/***** PUBLIC FUNCTIONS *****/

/** INIT FUNCTIONS **/


void DatabaseManager::dropDebugPrompt(string prompt) {
    cout << "[DataBaseManager] : " << prompt << endl;
}


vector<TransactionRecord> DatabaseManager::selectIncomes(vector<TransactionRecord> records_input) {
    vector<TransactionRecord> records_result;

    for (int cyc_tr = 0; cyc_tr < records_input.size(); cyc_tr ++) {
        if (records_input[cyc_tr].change > 0) {
            records_result.push_back(records_input[cyc_tr]);
        }
    }

    return records_result;
}

vector<TransactionRecord> DatabaseManager::selectExpenditures(vector<TransactionRecord> records_input) {

    vector<TransactionRecord> records_result;

    for (int cyc_tr = 0; cyc_tr < records_input.size(); cyc_tr ++) {
        if (records_input[cyc_tr].change <= 0) {
            records_result.push_back(records_input[cyc_tr]);
        }
    }

    return records_result;
}

vector<TransactionRecord> DatabaseManager::selectString(vector<TransactionRecord> records_input, string searched_string) {

    vector<TransactionRecord> records_result;

    for (int cyc_tr = 0; cyc_tr < records_input.size(); cyc_tr ++) {
        if (records_input[cyc_tr].note.find(searched_string) != string::npos) {
            records_result.push_back(records_input[cyc_tr]);
        }
    }

    return records_result;
}

vector<TransactionRecord> DatabaseManager::selectFilter(QString filter, vector<TransactionRecord> records_input){
    vector<TransactionRecord> records_output;

    if (filter == STRING_SELECT_FIELD_INCOME) {
        records_output = DatabaseManager::selectIncomes(records_input);
    }
    else if ( filter == STRING_SELECT_FIELD_EXPENDITURE ) {
        records_output = DatabaseManager::selectExpenditures(records_input);
    }
    else if ( filter ==  STRING_SELECT_FIELD_PAYPASS ) {
        records_output = DatabaseManager::selectString(records_input, "PPASS");
    }
    else if ( filter == STRING_SELECT_FIELD_CASHOUT ) {
        records_output = DatabaseManager::selectString(records_input, "ATM");
    }
    else {
        //QMessageBox::information(, "filter not correct", "filter is not iplemented yet :-(");
        records_output = records_input;
    }

    return records_output;
}
