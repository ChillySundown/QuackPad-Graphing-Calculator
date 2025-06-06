#ifndef DARWICH_FUNCTION_H
#define DARWICH_FUNCTION_H

#include <iostream>
#include <cassert>
#include "token.h"
#include "operator.h"
#include <cmath>
#include <cstring>

using namespace std;
class Function : public Operator {
    public:
        Function();

        Function(string f);

        virtual int typeOf();

        double eval(double e);

        virtual void printToken();
        
        string getFun();

        friend ostream& operator<<(ostream& outs, Function f);

    private:
        string my_fun;
};
#endif