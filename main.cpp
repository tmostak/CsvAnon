#include "CsvProcessor.h"
#include <iostream>
#include <string>
#include "Hash.h"
#include <boost/bind.hpp>
#include <unistd.h>
#include "boost/program_options.hpp"

using namespace std;

struct Args {
    string source; 
    string dest;
    bool hasHeader;
    char delim;
    HashType hashType;

    Args(): hasHeader(false), delim(','), hashType(HASH_SHA1) {}


};

namespace { 
    const size_t ERROR_IN_COMMAND_LINE = 1; 
    const size_t SUCCESS = 0; 
    const size_t ERROR_UNHANDLED_EXCEPTION = 2; 
       
} // namespace 

/*
void parseArguments(int argc, char* argv[], Args &args) { 
    int c;
    int digit_optind = 0;
    int shaOpt = 0;
    int headerOpt = 0;

}
*/

void printUsage (const string &programName) {
    cerr << "Usage: " << programName << " [OPTION]... SOURCE DEST" << endl;    
}

size_t parseArguments(int argc, char* argv[], Args &args) { 
    string hashTypeString;
    namespace po = boost::program_options;
    po::options_description desc("Options");
    desc.add_options()
    ("help,h", "Print help message")
    ("hash,H", po::value<std::string>(&hashTypeString), "Specify hash type (sha1 [DEFAULT], sha256 or sha512)");
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help") ) {
            printUsage(argv[0]);
            cout << desc << endl;
        }
        else {
            if (vm.count("hash") )  {
                cout << "hash found" << endl;
                cout << hashTypeString << endl;
            }
        }

            
    }
    catch (po::error &error) {
        cerr << "Error: " << error.what() << endl << endl;
        printUsage(argv[0]);
        cerr << desc << endl;
        return ERROR_IN_COMMAND_LINE; 
    }
    cout << hashTypeString << endl;
}



int main (int argc, char * argv[]) {
    Args args;
    size_t result = parseArguments(argc, argv, args);
    if (result != 0)
        return result;

    //catch (Exception &e) {}
}



    /*
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
*/

