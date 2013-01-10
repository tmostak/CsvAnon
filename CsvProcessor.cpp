#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <string>
#include <iostream>
#include "CsvProcessor.h"
//#include <boost/lexical_cast.hpp>



CsvProcessor::CsvProcessor(const string &_inFileName, const string &_outFileName, const char _delim, bool _hasHeader, Hash &_hash): inFileName(_inFileName), outFileName(_outFileName), delim(_delim), hasHeader(_hasHeader), delims(""), hash(_hash) {
    delims += delim; 
    inFile.open(inFileName.c_str());
    if (!inFile.good())
        throw Exception("Error opening file for reading");
    if (hasHeader)
        readHeaders(); // will also set numCols
    else
        numCols = getNumCols();
}

CsvProcessor::~CsvProcessor() {
    inFile.close();
    outFile.close();
}

void CsvProcessor::writeOutput() {
    inFile.seekg(0, ios::beg);
    //cout << outFileName << endl;
    outFile.open(outFileName.c_str());
    if (!outFile.is_open())
        throw Exception("Error opening file for writing");
    size_t lineNum = 0;
    while (inFile.good()) {
        string line;
        getline(inFile, line);
        //cout << line << endl;
        vector <string> tokens;
        splitLine(line, tokens);
        if (tokens.size() > 1) {
            if (lineNum != 0 || !hasHeader)  {
                for (set<size_t>::iterator scrambleIt = scrambledCols.begin(); scrambleIt != scrambledCols.end(); ++scrambleIt) {
                    if (tokens[*scrambleIt] != "")
                        hash(tokens[*scrambleIt]);
                }
            }
            for (vector<string>::iterator tokenIt = tokens.begin(); tokenIt != tokens.end(); ++tokenIt) {
                outFile << *tokenIt;
                if (tokenIt+1 != tokens.end()) 
                    outFile << delim;
            }
            outFile << endl;
            lineNum++;
        }
    }
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
    //cout << headerLine << endl;
    splitLine(headerLine, columnNames);
    numCols = columnNames.size();
    //cout << "Num Cols: " << numCols << endl;
    //for (int i = 0; i != numCols; i++)
        //cout << i << " " << columnNames[i] << endl;
}
    

void CsvProcessor::setScrambledColumnNames(const vector<string> &scrambledColumnNames) {
    scrambledCols.clear();
    for (vector<string>::const_iterator colIt = scrambledColumnNames.begin(); colIt != scrambledColumnNames.end(); ++colIt) {
        vector<string>::iterator findIt = find(columnNames.begin(), columnNames.end(), *colIt);
        if (findIt == columnNames.end()) {
            string errorString ("Column " + *colIt + " does not exist.");
            throw Exception (errorString);
        }
        else {
            size_t colIndex = findIt - columnNames.begin();
            scrambledCols.insert(colIndex);
        }
    }
}


void CsvProcessor::setScrambledColumnNums(const vector<size_t> &scrambledColumnNums) {
    scrambledCols.clear();
    size_t minElem = *min_element(scrambledColumnNums.begin(), scrambledColumnNums.end());
    size_t maxElem = *max_element(scrambledColumnNums.begin(), scrambledColumnNums.end());
    if (minElem < 1 || maxElem >= numCols) {
        string errorString ("Column index out of range.");
        throw Exception (errorString);
    }
    
    for (vector<size_t>::const_iterator colIt = scrambledColumnNums.begin(); colIt != scrambledColumnNums.end(); ++colIt) {
        size_t colNum = *colIt - 1;
        scrambledCols.insert(colNum);
        /*
        size_t colNum = *colIt; 
        if (colNum == 0) {
        if (*colIt - 1 >= numCols) {
            string errorString ("Column #" + boost::lexical_cast <string> (*colIt) + " does not exist.");
            throw Exception (errorString);
        }
        scrambledCols.insert(*colIt - 1);
        */
    }
}

    

        

        
        
    
    

    

