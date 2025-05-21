#ifndef DARWICH_RIGHT_PAREN
#define DARWICH_RIGHT_PAREN

#include <iostream>
#include <iomanip>

using namespace std;
class RightParen : public Token {
    public:
        RightParen();

        virtual int typeOf();

        virtual void printToken();

    private:
        string my_right_paren;
};

#endif