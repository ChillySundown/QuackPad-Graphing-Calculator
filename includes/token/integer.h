#ifndef DARWICH_INTEGER_H
#define DARWICH_INTEGER_H
#include "token.h"

using namespace std;

class Integer : public Token {
    public :
        Integer();
        Integer(double i);
        Integer(const char* i);

        virtual void printToken();

        virtual int typeOf();

        double getInt();

        double string_to_double(const char* str);

        friend ostream& operator<<(ostream& outs, Integer i);

    private :
        double myInt;
};
#endif