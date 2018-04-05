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
 * THis class responsible for sorting out tasks regarding table changes.
 * */

class TableManager
{


private:

public:

    TableManager();

    /*
     * It gives back the predefined labels in specific format
     * */
    static QStringList getLabels();



};

#endif // TABLEMANAGER_H
