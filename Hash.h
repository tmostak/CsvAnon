#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

#include <openssl/sha.h>

enum HashType {HASH_SHA256}; 

struct Hash {

    HashType hashType;

    void  sha256(string &str)
    {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, str.c_str(), str.size());
        SHA256_Final(hash, &sha256);
        stringstream ss;
        for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        {
            ss << hex << setw(2) << setfill('0') << (int)hash[i];
        }
        //return ss.str();
        str = ss.str();
    }

    Hash(const HashType _hashType): hashType(_hashType) {}

    void operator()(string & str) { // functor
        switch (hashType) {
            case HASH_SHA256: 
                sha256(str);
                break;  
        }
    }
};

#endif



