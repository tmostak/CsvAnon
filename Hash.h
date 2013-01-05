#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

#include <openssl/sha.h>

enum HashType {HASH_SHA1, HASH_SHA256, HASH_SHA512}; 

struct Hash {

    HashType hashType;

    void sha1 (string &str)
    {
        unsigned char hash[SHA_DIGEST_LENGTH];
        SHA_CTX sha1;
        SHA1_Init(&sha1);
        SHA_Update(&sha1, str.c_str(), str.size());
        SHA1_Final(hash, &sha1);
        stringstream ss;
        for(int i = 0; i < SHA_DIGEST_LENGTH; i++)
        {
            ss << hex << setw(2) << setfill('0') << (int)hash[i];
        }
        str = ss.str();
    }

    void sha256(string &str)
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
        str = ss.str();
    }

    void sha512(string &str)
    {
        unsigned char hash[SHA512_DIGEST_LENGTH];
        SHA512_CTX sha512;
        SHA512_Init(&sha512);
        SHA512_Update(&sha512, str.c_str(), str.size());
        SHA512_Final(hash, &sha512);
        stringstream ss;
        for(int i = 0; i < SHA512_DIGEST_LENGTH; i++)
        {
            ss << hex << setw(2) << setfill('0') << (int)hash[i];
        }
        str = ss.str();
    }

    Hash(const HashType _hashType): hashType(_hashType) {}

    void operator()(string & str) { // functor
        switch (hashType) {
            case HASH_SHA1: 
                sha1(str);
                break;  
            case HASH_SHA256: 
                sha256(str);
                break;  
            case  HASH_SHA512: 
                sha512(str);
                break;  
        }
    }
};

#endif



