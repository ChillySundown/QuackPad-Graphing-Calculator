#ifndef DARWICH_RPN_H
#define DARWICH_RPN_H

#include "../../includes/token/token.h"
#include "../../includes/token/operator.h"
#include "../../includes/token/integer.h"
#include "../../includes/token/function.h"
#include "../../includes/token/leftparen.h"
#include "../../includes/token/rightparen.h"

#include "../../includes/queue/MyQueue.h"

#include "../../includes/shunting_yard/shunting_yard.h"
#include "../../includes/rpn/rpn.h"

class RPN {
    public:
        RPN();
        
        RPN(Queue<Token*> q);

        void set_input(Queue<Token*> q);

        double calculate(double x);

        double operator()(double x = 0);

    private:
        Queue<Token*> postfix;
        Stack<double> math_stack;
};
#endif