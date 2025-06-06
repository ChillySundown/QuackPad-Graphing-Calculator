#include <iostream>
#include <cassert>
#include "rpn.h"
#include "../../includes/token/token.h"

using namespace std;

RPN::RPN() {

}

RPN::RPN(Queue<Token*>& q) {
    postfix = q;
    math_stack = Stack<double>();
}

void RPN::set_input(Queue<Token*> q) {
    postfix = q;
    math_stack = Stack<double>();
}

double RPN::calculate(double x) {
    while(!postfix.empty()) {
        Token* current = postfix.pop();
        if(current->typeOf() == INTEGER) {
            math_stack.push(static_cast<Integer*>(current)->getInt());
        }
        else {
            if(current->typeOf() == FUNCTION) {
                double val = x;
                if(!math_stack.empty() && static_cast<Function*>(current)->getFun() != "x") { //X is an input variable, so it should always be equal to input
                    val = math_stack.pop(); //This sets other functions, like trig, to the top number in the stack.
                }
                math_stack.push(static_cast<Function*>(current)->eval(val));
            }
            else if(current->typeOf() == OPERATOR) {
                if(static_cast<Operator*>(current)->getVal() == NEGATE) {
                    double negative = -1 * math_stack.pop(); 
                    math_stack.push(negative);
                }
                else {
                    double second = math_stack.pop();
                    double first = math_stack.pop();
                    double val = static_cast<Operator*>(current)->evaluate(first, second); //Returns value of operation done on first & second
                    math_stack.push(val); //Pushes the new value to the math stack
                }
            }
        }
    }
    double top = math_stack.pop();
    //cout << top << endl;
    return top;
}

double RPN::operator()(double x) {
    return calculate(x);
}