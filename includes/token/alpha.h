#ifndef DARWICH_ALPHA_H
#define DARWICH_ALPHA_H
#include "token.h"
#include <iostream>

using namespace std;

class Alpha : public Token {
    public: 
        Alpha();
        Alpha(char c);

        virtual int typeOf();

        virtual void printToken();

    private:
        char my_char;
};
#endif