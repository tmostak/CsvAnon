#include "CsvProcessor.h"
#include <iostream>

int main () {

    try {
        CsvProcessor("allahabad_sample_cdr.csv", "allahabad_out.csv", ',', true);
    }
    catch (Exception e) {
        cout << "Error: " << e.errorString << endl;
    }
}

