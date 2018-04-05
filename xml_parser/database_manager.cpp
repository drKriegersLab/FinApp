#include "xml_parser_main.h"
#include "database_manager.h"

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

vector<TransactionRecord> DatabaseManager::selectFilter(QString filter, vector<TransactionRecord> records_input){
    vector<TransactionRecord> records_output;

    if (filter == "income") {
        records_output = DatabaseManager::selectIncomes(records_input);
    }
    else if ( filter == "expenditure" ) {
        records_output = records_input;
        //records_output = DbManager->selectExpenditures(records_input);
    }
    else if ( filter ==  "paypass" ) {
        records_output = records_input;
        //records_output = DbManager->selectPpassPayments(records_input);
    }
    else if ( filter == "chashout" ) {
        records_output = records_input;
        //records_output = DbManager->selectCashouts(records_input);
    }
    else {
        //QMessageBox::information(, "filter not correct", "filter is not iplemented yet :-(");
        records_output = records_input;
    }

    return records_output;
}
