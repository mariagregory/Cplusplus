/* 
 * File:   floatSp.h
 * Author: Maria Gregory
 *
 * Created on April 20, 2018, 7:49 PM
 */

#ifndef FLOATSP_H
#define FLOATSP_H

#include <cstring>
#include <iostream>
using namespace std;
const short binSize = 33, hexSize = 9, rawSize=9; // +1 for null terminator

class floatSp {
    private:
        float number;
        char binary[binSize];
        char hexadec[hexSize];
        char binRaw[rawSize]; // "raw" binary
        char hexRaw[rawSize]; //"raw" hexadecimal
        char octRaw[rawSize]; //"raw" octal
    public:
        floatSp(float num, const char* bin, const char *hex, 
                const char *binRaw, const char *hexRaw, const char *oct) {
            number = num;
            strncpy(binary, bin, binSize);
            strncpy(hexadec, hex, hexSize);
            strncpy(this->binRaw, binRaw, rawSize);
            strncpy(this->hexRaw, hexRaw, rawSize);
            strncpy(octRaw, oct, rawSize);
        };
        float getNum() const { return number; }
        char *getBin()  { return binary; }
        char *getHex()  { return hexadec; }
        char *getBRaw()  { return binRaw; }
        char *getHRaw()  { return hexRaw; }
        char *getORaw()  { return octRaw; }
};

#endif /* FLOATSP_H */

