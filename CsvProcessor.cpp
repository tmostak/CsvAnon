#include <boost/algorithm/string.hpp>
#include <algorithm>

CsvScrambler::CsvScrambler(const string &_inFileName, const string &_outFileName, const char _delim, bool _hasHeader): inFileName(_inFileName), delim(_delim), hasHeader(_hasHeader) {
    delims("\n" + delim); 
    inFile.open(inFileName);
    if (!inFile.good())
        throw Exception("Error opening file");
    if (hasHeader)
        readHeaders(); // will also set numCols
    else

}

CsvScrambler::~CsvScrambler() {
    inFile.close();
    outFile.close();
}

size_t CsvParser::getNumCols() { // returns num cols and moves file pointer back to original position
    size_t curPos = inFile.tellg();
    inFile.seekg(0, ios::begin);
    string line;
    getline(inFile, headerLine);
    vector <string> tokens;
    splitLine(line, tokens);
    numCols = tokens.size(); 
    inFile.seekg(curPos, ios::begin);
}
    


void CsvParser::splitLine(const string &line, vector <string> &tokens) {
    boost::split(tokens, query, boost::is_any_of(delims));
}

void CsvParser::readHeaders() {
     
    string headerLine;
    getline(inFile, headerLine);
    splitLine(headerLine, columnNames);
    numCols = columnNames.size();
    cout << "Num Cols: " << numCols << endl;
}
    

void CsvParser::setScrambledColumns(const vector<string> &scrambledColumns) {
    for (vector<string>::iterator colIt = scrambledColumns.begin(); colIt != scrambledColumns.end(); ++colIt) {
        vector<string>::iterator findIt = find(columnNames.begin(), columnNames.end(), *colIt);
        if (findIt == columnNames.end()) {
            string errorString ("Error: column " + *colIt + " does not exist.");
            throw Exception (errorString);
        }
        else {
            size_t colIndex = findIt - columnNames.begin();
            convertCols.insert(colIndex);
        }
    }
}



        
        
    
    

    

