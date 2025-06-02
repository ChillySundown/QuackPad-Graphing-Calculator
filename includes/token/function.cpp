#include <iostream>
#include <iomanip>
#include <cassert>
#include "function.h"
#include "token.h"

Function::Function() : Operator(), my_fun("") {

}

Function::Function(string f) : Operator(f), my_fun(f) {

}

int Function::typeOf() {
    return FUNCTION;
}

double Function::eval(double e) { //May not work for sin, cos, etc; Just used to substitute X and Y for rpn value.
    if(my_fun == "sin") {
        return sin(e);
    }
    else if(my_fun == "cos") {
        return cos(e);
    }
    else if(my_fun == "tan") {
        return tan(e);
    }
    else {
        return e;
    }
}

void Function::printToken() {
    cout << my_fun;
}

ostream& operator<<(ostream& outs, Function f) {
    f.printToken();
    return outs;
}

