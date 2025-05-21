#include "integer.h"
#include <iostream>
#include <iomanip>
using namespace std; 

Integer::Integer() {
    Token();
    myInt = 0;
}

Integer::Integer(double i) {
    Token();
    myInt = i;
}

Integer::Integer(const char* i) {
    Token();
    myInt = string_to_double(i);
}

int Integer::typeOf() {
    return INTEGER;
}

void Integer::printToken() {
    cout << myInt;
}

double Integer::getInt() {
    return myInt;
}

ostream& operator<<(ostream& outs, Integer i) {
    i.printToken();
    return outs;
}

double Integer::string_to_double(const char* str) {
    double dbl_val = 0;
    const char* w = str;
    while(*w != '\0' && *w != '.') {
        double current = *w - 48;
        dbl_val *= 10;
        dbl_val += current;
        w++;
    }

    if(*w != '\0') {
        w++;
        double num_place = 0.1;
        while(*w != '\0') {
            double current = *w - 48;
            dbl_val += current * num_place;
            num_place /= 10;
            w++;
        }
    }
    return dbl_val;
}