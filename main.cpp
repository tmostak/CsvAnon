#include "CsvProcessor.h"
#include <iostream>
#include "Hash.h"
#include <boost/bind.hpp>
#include <unistd.h>

using namespace std;

struct Args {
    string inFileName; 
    string outFileName;
    bool hasHeader;
    char delim;
    HashType hashType;
};

void parseArguments(int argc, char* argv[], Args &args) { 
    int c;
    int digit_optind = 0;
    int shaOpt = 0;
    int headerOpt = 0;

}



void printUsage (const string &programName) {
    cerr << "Usage: " << programName << " IN_FILE OUT_FILE" << endl;     
}

int main (int argc, char* argv[]) {
    Args args;
    parseArguments(argc, argv, args); 
    cout << argc << endl;

    if (argc < 3) {
        printUsage(argv[0]);
        return 1;
    }
    
    try {
        Hash hash(HASH_SHA1);
        CsvProcessor csvProcessor ("allahabad_sample_cdr.csv", "allahabad_out.csv", ',', true, hash);
        vector <string> scrambledCols;
        //scrambledCols.push_back("IMSI");
        scrambledCols.push_back("ACCESS_METHOD_IDENTIFIER");
        csvProcessor.setScrambledColumns(scrambledCols);
        csvProcessor.writeOutput();
    }
    catch (Exception e) {
        cerr << "Error: " << e.errorString << endl;
        return 2;
    }
}

