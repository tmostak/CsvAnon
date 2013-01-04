#include "CsvProcessor.h"
#include <iostream>

int main () {

    try {
        CsvProcessor csvProcessor ("allahabad_sample_cdr.csv", "allahabad_out.csv", ',', true);
        vector <string> scrambledCols;
        scrambledCols.push_back("IMSI");
        csvProcessor.setScrambledColumns(scrambledCols);
        csvProcessor.writeOutput();
    }
    catch (Exception e) {
        cout << "Error: " << e.errorString << endl;
    }
}

