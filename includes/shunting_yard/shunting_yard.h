#ifndef DARWICH_SHUNTING_YARD_H
#define DARWICH_SHUNTING_YARD_H

#include <iostream>
#include <iomanip>
#include "../stack/MyStack.h"
#include "../queue/MyQueue.h"
#include "../token/token.h"
#include "../token/operator.h"
#include "../token/function.h"
#include "../token/rightparen.h"
#include "../token/leftparen.h"
class ShuntingYard {
    public:

        ShuntingYard();

        ShuntingYard(Queue<Token*>& q);

        Queue<Token*> postfix();

        Queue<Token*> postfix(Queue<Token*>& my_queue);

        void infix(Queue<Token*>& q);

        friend ostream& operator<<(ostream& outs, ShuntingYard s);

    private:
        Queue<Token*> my_queue;
        void operator_protocol(Queue<Token*>& q, Stack<Token*>& s, Token* t);
        void paren_protocol(Queue<Token*>& q, Stack<Token*>& s, Token* t);
};
#endif