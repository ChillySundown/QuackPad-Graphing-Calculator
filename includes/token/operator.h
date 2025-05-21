#ifndef DARWICH_OPERATOR_H
#define DARWICH_OPERATOR_H

#include "token.h"

using namespace std;

enum OPS {PLUS, MINUS = 0, MULTIPLY = 1, DIVIDE = 1, EXPONENT = 2};
class Operator : public Token {
    public:
        Operator();

        Operator(string op);

        virtual int typeOf();

        int getVal();

        double evaluate(double first, double second);

        virtual void printToken();

        friend bool operator>(Operator o1, Operator o2);

        friend bool operator<=(Operator o1, Operator o2);

    private:
        string my_op;
        int specific_op;
};
#endif