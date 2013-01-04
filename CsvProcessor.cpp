#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <iostream>
#include "CsvProcessor.h"

CsvProcessor::CsvProcessor(const string &_inFileName, const string &_outFileName, const char _delim, bool _hasHeader): inFileName(_inFileName), delim(_delim), hasHeader(_hasHeader), delims("\n") {
    delims += delim; 
    inFile.open(inFileName.c_str());
    if (!inFile.good())
        throw Exception("Error opening file");
    if (hasHeader)
        readHeaders(); // will also set numCols
    else
        numCols = getNumCols();
}

CsvProcessor::~CsvProcessor() {
    inFile.close();
    outFile.close();
}

size_t CsvProcessor::getNumCols() { // returns num cols and moves file pointer back to original position
    size_t curPos = inFile.tellg();
    inFile.seekg(0, ios::beg);
    string line;
    getline(inFile, line);
    vector <string> tokens;
    splitLine(line, tokens);
    numCols = tokens.size(); 
    inFile.seekg(curPos, ios::beg);
}
    


void CsvProcessor::splitLine(const string &line, vector <string> &tokens) {
    boost::split(tokens, line, boost::is_any_of(delims));
}

void CsvProcessor::readHeaders() {
     
    string headerLine;
    getline(inFile, headerLine);
    cout << headerLine << endl;
    splitLine(headerLine, columnNames);
    numCols = columnNames.size();
    cout << "Num Cols: " << numCols << endl;
    for (int i = 0; i != numCols; i++)
        cout << i << " " << columnNames[i] << endl;
}
    

void CsvProcessor::setScrambledColumns(const vector<string> &scrambledColumns) {
    for (vector<string>::const_iterator colIt = scrambledColumns.begin(); colIt != scrambledColumns.end(); ++colIt) {
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



        
        
    
    

    

