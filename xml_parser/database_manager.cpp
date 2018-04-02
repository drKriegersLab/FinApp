#include "xml_parser_main.h"
#include "database_manager.h"

/***** PUBLIC FUNCTIONS *****/

/** INIT FUNCTIONS **/
DatabaseManager::DatabaseManager(float init_balance) {

    initDB(init_balance);
}

DatabaseManager::DatabaseManager(float init_balance, CsvFields csvContent[], size_t num_of_lines) {

    initDB(init_balance);
    addCsvToDB(csvContent, num_of_lines);
}

DatabaseManager::DatabaseManager(float init_balance, string filename) {
    string *csv_lines; //container of csv content
    int num_of_lines; //number of csv lines

    initDB(init_balance);

    dropDebugPrompt("reading specified file and get its valid lines...");
    CSV_reader Reader(filename);
    Reader.readFile();
    Reader.getNumOfLines(&num_of_lines);
    csv_lines = new string[num_of_lines];
    Reader.getLines(&csv_lines);

    dropDebugPrompt("parsing csv content...");
    CSV_parser Parser(csv_lines, num_of_lines);
    Parser.parseFile();

    dropDebugPrompt("geting parsed records...");
    CsvFields *csv_content;
    Parser.getCsvRecords(&csv_content);

    dropDebugPrompt("storing records into the database...");
    addCsvToDB(csv_content, num_of_lines);
    //printAllTransactions();




}

int DatabaseManager::addCsvToDB(CsvFields csvContent[], size_t num_of_lines) {

    dropDebugPrompt("storing new CSV content...");

    float balance_last = transactions[num_of_records -1].balance;
    // store csv records to transaction temp database
    TransactionRecord* tmpTransactions = new TransactionRecord[num_of_lines];

    for (size_t rec_id = 0; rec_id < num_of_lines; rec_id ++) {

        tmpTransactions[rec_id].change = (float)csvContent[rec_id].change;

        balance_last += csvContent[rec_id].change;
        tmpTransactions[rec_id].balance = balance_last;
        tmpTransactions[rec_id].currency = csvContent[rec_id].currency;
        tmpTransactions[rec_id].date = new QDate(csvContent[rec_id].date_of_realization.yy, csvContent[rec_id].date_of_realization.mm, csvContent[rec_id].date_of_realization.dd);
        tmpTransactions[rec_id].note = csvContent[rec_id].note;
        //csvContent[rec_id].date_of_realization;
        //tmpTransactions[rec_id].partner_id = csvContent[rec_id].from_partner_id;
        /*tmpTransactions[rec_id].partner_name = csvContent[rec_id].from_partner_name;
        tmpTransactions[rec_id].tr_type = csvContent[rec_id].transaction_type;
        tmpTransactions[rec_id].tr_note = csvContent[rec_id].transaction_note + csvContent[rec_id].transaction_note2;
        tmpTransactions[rec_id].tr_name = csvContent[rec_id].transaction_note + csvContent[rec_id].transaction_note2;*/
        //tmpTransactions[rec_id].tr_note << csvContent[rec_id].transaction_note2;
    }

    // append temporary database to the commond database
    appendNewRecords(tmpTransactions, num_of_lines);

    dropDebugPrompt("storing finished");

    return 0;
}


void DatabaseManager::printAllTransactions() {
    // header
    printf("#######################\nall recorded transactions:\n");
    cout << "the number of transactions: " << num_of_records << endl;

    // list generation
    for (size_t tr_id = 0; tr_id < num_of_records; tr_id++) {
        printf("*********************************\n");
        cout << "id:          " << tr_id << endl;
        cout << "currency:    " << transactions[tr_id].currency << endl;
        cout << "change:      " << transactions[tr_id].change << endl;
        cout << "new balance: " << transactions[tr_id].balance << endl;
        //cout << "date:        " << transactions[tr_id].date << endl;
        //cout << "name:        " << transactions[tr_id].tr_name << endl;
        //cout << "partner id:  " << transactions[tr_id].partner_id << endl;
        //cout << "trans. type: " << transactions[tr_id].tr_type << endl;

    }

    // foot
    printf("\nend of list\n#######################");
}

void DatabaseManager::getTransaction(int record_id, TransactionRecord* record) {
    TransactionRecord rec; // = new TransactionRecord();

    rec.currency = transactions[record_id].currency;
    rec.change = transactions[record_id].change;
    rec.balance = transactions[record_id].balance;
    rec.note = transactions[record_id].note;
    //rec.tr_name = transactions[record_id].tr_name;
    //rec.partner_id = transactions[record_id].partner_id;
    //rec.tr_type = transactions[record_id].tr_type;

    *record = rec;

    //cout << "bal: " << record->balance << endl;

}

void DatabaseManager::getAllTransactions(TransactionRecord *records[]) {
    *records = transactions;
}

int DatabaseManager::getNumOfTransactions() {
    return num_of_records;
}

/***** PRIVATE FUNCTIONS *****/

int DatabaseManager::initDB(float init_balance) {

    dropDebugPrompt("init database");
    // init DB with one element
    transactions = new TransactionRecord[1];

    transactions[0].change = init_balance;
    transactions[0].balance = init_balance;
    transactions[0].currency = "HUF";
    transactions[0].note = "init balance";
    transactions[0].date = new QDate(2017, 1, 1);
    // start date
    /*
    DateStruct date_first  = new DateStruct;
    date_first.dd = 1;
    date_first.mm = 1;
    date_first.yy = 2016;

    transactions[0].date = date_first;

    transactions[0].tr_name = "balance initialization";
    transactions[0].partner_id = "";
    transactions[0].tr_type = "init";
    */
    // init num_of_records
    num_of_records = 1;

    dropDebugPrompt("database initialized");
}

int DatabaseManager::appendNewRecords(TransactionRecord records[], size_t num_of_new_records) {

    dropDebugPrompt("appending new content to the database");
    // save the original DB
    TransactionRecord* oldTransactions = transactions;

    // reset database, and init with its new size
    transactions = new TransactionRecord[num_of_records + num_of_new_records];

    // copy the original part back to the DB
    for (size_t tr_id = 0; tr_id < num_of_records; tr_id ++) {
        transactions[tr_id] = oldTransactions[tr_id];
    }

    // copy the new part after the original one
    for (size_t tr_id = 0; tr_id < num_of_new_records; tr_id++) {
        transactions[num_of_records + tr_id] = records[tr_id];
    }

    // update the num_of_records
    num_of_records += num_of_new_records;

    dropDebugPrompt("appending finished");
    return 0;

}


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
