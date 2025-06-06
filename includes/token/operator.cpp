#include <iostream>
#include <iomanip>
#include <cassert>
#include "operator.h"
#include <cmath>

Operator::Operator() {
    Token();
    my_op = "";
    specific_op = 0;

}

Operator::Operator(string op) {
    Token();
    my_op = op;
    if(op == "+") {
        specific_op = PLUS;
    }
    else if(op == "-") {
        specific_op = MINUS;
    }
    else if(op == "*") {
        specific_op = MULTIPLY;
    }
    else if(op == "/") {
        specific_op = DIVIDE;
    }
    else if(op == "^") {
        specific_op = EXPONENT;
    }
    else if(op == "u-") {
        specific_op == NEGATE;
    }
    else {
        specific_op = 4; //Hidden Modulus operator??
    }
}

int Operator::typeOf() {
    return OPERATOR;
}

void Operator::printToken() {
    cout << my_op;
}

double Operator::evaluate(double first, double second) {
    if(my_op == "+") {
        return first + second;
    }
    else if(my_op == "-") {
        return first - second;
    }
    else if(my_op == "*") {
        return first * second;
    }
    else if(my_op == "/") {
        return first / second;
    }
    else if(my_op == "^") {
        return pow(first, second);
    }
    return 99813942; //ERROR CODE
 
}

bool operator>(Operator o1, Operator o2) { //Overloading the > operator; Ex: popped_op > stack_top()
    if(o1.specific_op > o2.specific_op) {
        return true;
    }
    return false;
}

bool operator<=(Operator o1, Operator o2) {
    return !(o1 > o2);
}

int Operator::getVal() {
    return specific_op;
}