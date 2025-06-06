#ifndef DARWICH_OPERATOR_H
#define DARWICH_OPERATOR_H

#include "token.h"

using namespace std;

enum OPS {NEGATE, PLUS=1, MINUS = 1, MULTIPLY = 2, DIVIDE = 2, EXPONENT = 3};
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