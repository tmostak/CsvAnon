#include "CsvProcessor.h"
#include <iostream>
#include "Hash.h"
#include <boost/bind.hpp>

int main () {

    try {
        Hash hash(HASH_SHA256);
        CsvProcessor csvProcessor ("allahabad_sample_cdr.csv", "allahabad_out.csv", ',', true, hash);
        vector <string> scrambledCols;
        //scrambledCols.push_back("IMSI");
        scrambledCols.push_back("ACCESS_METHOD_IDENTIFIER");
        csvProcessor.setScrambledColumns(scrambledCols);
        csvProcessor.writeOutput();
    }
    catch (Exception e) {
        cout << "Error: " << e.errorString << endl;
    }
}

