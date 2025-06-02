#include <iostream>
#include <cassert>
#include "rpn.h"
#include "../../includes/token/token.h"

using namespace std;

RPN::RPN() {
    
}

RPN::RPN(Queue<Token*> q) {
    postfix = q;
    math_stack = Stack<double>();
}

void RPN::set_input(Queue<Token*> q) {
    postfix = q;
    
}

double RPN::calculate(double x) {
    while(!postfix.empty()) {
        Token* current = postfix.pop();
        if(current->typeOf() == INTEGER) {
            math_stack.push(static_cast<Integer*>(current)->getInt());
        }
        else {
            if(current->typeOf() == FUNCTION) {
                math_stack.push(static_cast<Function*>(current)->eval(x));
            }
            else if(current->typeOf() == OPERATOR) {
                double second = math_stack.pop();
                double first = math_stack.pop();
                double val = static_cast<Operator*>(current)->evaluate(first, second); //Returns value of operation done on first & second
                math_stack.push(val); //Pushes the new value to the math stack
            }
        }
        //cout << math_stack << endl;
    }
    return math_stack.pop();
}

double RPN::operator()(double x) {
    return calculate(x);
}