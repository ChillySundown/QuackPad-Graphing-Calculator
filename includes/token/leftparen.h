#ifndef DARWICH_LEFT_PAREN_H
#define DARWICH_LEFT_PAREN_H
#include <iostream>
#include <iomanip>
#include "token.h"

using namespace std;

class LeftParen : public Token {
    public:
        LeftParen();
        
        virtual int typeOf();

        virtual void printToken();

    private:
        string my_left_paren;
};

#endif