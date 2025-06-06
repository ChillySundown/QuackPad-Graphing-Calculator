#include <iostream>
#include <iomanip>
#include <cassert>
#include "function.h"
#include "token.h"
#include <cmath>

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
    else if(my_fun == "arccos") {
        return acos(e);
    }
    else if(my_fun == "arcsin") {
        return asin(e);
    }
    else if(my_fun == "arctan") {
        return atan(e);
    }
    else if(my_fun == "pi") {
        return 4 * atan(1);
    }
    else {
        return e;
    }
}

string Function::getFun() {
    return my_fun;
}

void Function::printToken() {
    cout << my_fun;
}

ostream& operator<<(ostream& outs, Function f) {
    f.printToken();
    return outs;
}

