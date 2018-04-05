
#include "xml_parser_main.h"
#include "csv_input.h"
#include "parse_csv.h"
#include "database_manager.h"

int xml_parser_main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CSV_reader reader("/home/drkrieger/01_PetProjects/xml_parser/xml_base/2017_01.csv");
    reader.readFile();

    string *lines;
    int num_lines;
    cout << "getlines" << endl;

    reader.getNumOfLines(&num_lines);
    lines = new string[num_lines];
    reader.getLines(&lines);

    CSV_parser Parser(lines, num_lines);
    Parser.parseFile();

    CsvFields *csvContent;
    Parser.getCsvRecords(&csvContent);

    //DatabaseManager dataBase(100000);

    //dataBase.addCsvToDB(csvContent, num_lines);

    //dataBase.printAllTransactions();



    //getchar();
    return 0;

    //return a.exec();
}
