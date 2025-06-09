#ifndef DARWICH_CONSTANTS_H
#define DARWICH_CONSTANTS_H

#include <iostream>
#include <iomanip>
#include <cassert>
#include "token.h"

using namespace std;
class Constants : public Token {
    public:
        Constants();

        Constants(string c);

    private:
        string my_constant;
};
#endif