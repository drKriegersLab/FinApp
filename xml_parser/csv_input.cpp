#include "csv_input.h"
#include <typeinfo>

CSV_reader::CSV_reader(string filename) {
    fname = filename;
}

int CSV_reader::readFile() {
    cout << "reading file " << fname << endl;
    ifstream infile;
    string line;
    // open file and count the number of lines and after that close it. With this method, I can check the file is alid or not, and I can allocate
    // dynamically the container array
    infile.open(fname);
    num_of_valid_lines = 0;
    while(getline(infile, line)){
        num_of_valid_lines++;
    }

    cout << "num of lines: " << num_of_valid_lines << endl;

    infile.close();

    // if there are valid lines, reopen it, and save the content line by line into the scv_content into the dynamically allocated array
    if (num_of_valid_lines != 0) {
        csv_content = new string[num_of_valid_lines];
        int linenum = 0;
        infile.open(fname);
        while(getline(infile, line)) {
            csv_content[linenum] = line;
            linenum++;
        }

        infile.close();
        return 0;
    }
    else {
        cout << "[ERR] there are no lines in this file: " << fname << endl;
        return -1;
    }
}


int CSV_reader::printLines() {
    printf("printing conatined lines of file\n");
    for (int line_num = 0; line_num < num_of_valid_lines; line_num++) {
        cout << line_num << " : " << csv_content[line_num] << endl;
    }
    printf("end of lines\n");
    return 0;
}

int CSV_reader::getNumOfLines(int *number_of_lines){
    *number_of_lines = num_of_valid_lines;
    return 0;
}

int CSV_reader::getLines(string *lines[]) {
    *lines = csv_content;
    return 0;
}

