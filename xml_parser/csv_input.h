#ifndef CSV_INPUT_H
#define CSV_INPUT_H



#include "xml_parser_main.h"

int read_file();

#define CSVMAXLINES 50

class CSV_reader {

    /*** private variables ***/
    string fname; // filename of csv file
    int num_of_valid_lines = 0; // internal variable for representing, how many lines are in the csv file
    //string csvLines[CSVMAXLINES] = {}; // internal container of read lines out of csv file
    string *csv_content; // dynamically allocated string array for storing the csv file's content


    /*** public functions ***/
public:
    /* init function for initializing the object and storing important information */
    CSV_reader(string filename);

    /* function for reading csv file and storing the content of it */
    int readFile();

    int printLines();

    /*** get functions ***/

    /* function for determining the size of dynamically allocated container */
    int getNumOfLines(int *number_of_lines);

    /* get the container */
    int getLines(string *lines[]);

};

#endif // CSV_INPUT_H
