#ifndef CSVPROCESSOR_h 
#define CSVPROCESSOR_h 

#include <vector>
#include <string> 
#include <fstream>
#include <set>
#include <vector>
#include "Hash.h"
//#include <boost/function.hpp>
//#include <exception>

using namespace std;

struct Exception  {
    string errorString;
    Exception (const string &_errorString): errorString(_errorString){}
};

class CsvProcessor {
    
    private:
        //boost::function <void(string)> hashFunc;
        Hash &hash;
        ifstream inFile;
        ofstream outFile;
        string inFileName;
        string outFileName;
        vector <string> columnNames;
        set <size_t> scrambledCols;
        size_t numCols;
        char delim;
        string delims;
        bool hasHeader;
        void splitLine(const string &line, vector <string> &tokens);
        void readHeaders();
        size_t getNumCols(); // returns num cols and moves file pointer back to original position
        /*
        inline void CsvParser::splitLine(const string &line, vector <string> &tokens) {
            boost::split(tokens, query, boost::is_any_of(delims));
        }
        */

    public:
        CsvProcessor (const string &_inFileName, const string &_outFileName, const char _delim, bool _hasHeader, Hash &_hash);
        ~CsvProcessor();
        void setScrambledColumnNames(const vector <string> &scrambledColumnNames);
        void setScrambledColumnNums(const vector<size_t> &scrambledColumnNums);
        void writeOutput();
};

#endif


