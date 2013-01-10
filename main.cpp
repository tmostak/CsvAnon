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
    vector <string> scrambledColNames;
    vector <size_t> scrambledColNums;
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
    namespace po = boost::program_options;
    po::options_description desc("Options");
    desc.add_options()
    ("help,h", "Print help message")
    ("func,f", po::value<std::string>(), "hash function (sha1 [DEFAULT], sha256 or sha512)")
    ("delim,d", po::value<char>(), "CSV delimiter (',' [DEFAULT] )")
    ("header,H", "source CSV file has header")
    ("vars,v", po::value<std::vector <std::string> >(&args.scrambledColNames), "names of columns to be anonymized (only valid with header option)")
    ("indices,i", po::value<std::vector <size_t> >(&args.scrambledColNums), "column indices of columns to be anonymized")
    ("source",po::value<std::string>(&args.source)->required(), "source file")
    ("dest",po::value<std::string>(&args.dest)->required(), "destination file");

    po::positional_options_description positionalOptions;
    positionalOptions.add("source", 1);
    positionalOptions.add("dest", 1);


    po::variables_map vm;
    try {
        po::store(po::command_line_parser(argc, argv).options(desc).positional(positionalOptions).run(), vm);

        if (vm.count("help") ) {
            printUsage(argv[0]);
            cout << desc << endl;
            return SUCCESS;
        }
        po::notify(vm);
        if (vm.count("hash") )  {
            cout << "hash found" << endl;
            string hashTypeString (vm["hash"].as<string>());
            if (hashTypeString == "sha1")
                args.hashType = HASH_SHA1;
            else if (hashTypeString == "sha256")
                args.hashType = HASH_SHA256;
            else if (hashTypeString == "sha512")
                args.hashType = HASH_SHA512;
            else 
                boost::throw_exception(po::error("invalid hash type"));
            cout << vm["hash"].as<string>() << endl; 
        }
        if (vm.count("delim")) {
            cout << "delim found" << endl;
            args.delim = vm["delim"].as<char>();
        }
        if (vm.count("header")) 
            args.hasHeader = true;
        if (vm.count("vars")) {
            if (!args.hasHeader) 
                boost::throw_exception(po::error("column names without header invalid"));
            if (vm.count("cols"))
                boost::throw_exception(po::error("column names with indicies invalid"));
        }

    }
    catch (po::error &error) {
        cerr << "Error: " << error.what() << endl << endl;
        printUsage(argv[0]);
        cerr << desc << endl;
        return ERROR_IN_COMMAND_LINE; 
    }
    return SUCCESS;
}



int main (int argc, char * argv[]) {
    Args args;
    size_t result = parseArguments(argc, argv, args);
    if (result != 0)
        return result;
    try {
        Hash hash(args.hashType);
        CsvProcessor csvProcessor (args.source, args.dest, args.delim, args.hasHeader, hash);
        if (args.scrambledColNames.size() != 0)
            csvProcessor.setScrambledColumnNames(args.scrambledColNames);
        else if (args.scrambledColNums.size() != 0)
            csvProcessor.setScrambledColumnNums(args.scrambledColNums);


        csvProcessor.writeOutput();
    }
    catch (Exception e) {
        cerr << "Error: " << e.errorString << endl;
        return 2;
    }



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

