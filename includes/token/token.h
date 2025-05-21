#ifndef DARWICH_TOKEN_H
#define DARWICH_TOKEN_H

#include <cstring>
#include <iostream>
#include <cassert>

using namespace std;

enum TYPES {TOKEN, INTEGER, OPERATOR, RIGHT_PAREN, LEFT_PAREN, FUNCTION}; 

class Token {
    public:
        Token();
        Token(string str);

        virtual int typeOf();

        virtual void printToken();

        friend ostream& operator<<(ostream& outs, Token* k);

    private:
        string my_str;
};
#endif