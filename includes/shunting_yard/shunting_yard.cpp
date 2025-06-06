#include <iostream>
#include <iomanip>
#include "shunting_yard.h"
#include "../token/token.h"
#include "../queue/MyQueue.h"
#include "../stack/MyStack.h" 
#include "../token/operator.h"

ShuntingYard::ShuntingYard() {
    
}

ShuntingYard::ShuntingYard(Queue<Token*>& q) {
    my_queue = q;
}

void ShuntingYard::operator_protocol(Queue<Token*>& q, Stack<Token*>& s, Token* t) {
    Operator* o = static_cast<Operator*>(t);
    while(!s.empty() && (s.top())->typeOf() != LEFT_PAREN && o->getVal() <= static_cast<Operator*>(s.top())->getVal()) { //Better than the egregious (*o <= *(static_cast<Operator*>(s.top())))
        q.push(s.pop());
    }
    s.push(o);
}

void ShuntingYard::paren_protocol(Queue<Token*>& q, Stack<Token*>& s, Token* t) {
    t = static_cast<RightParen*>(t);
    while(!s.empty() && s.top()->typeOf() != LEFT_PAREN) {
        q.push(s.pop());
    }
    if(!s.empty() && s.top()->typeOf() == LEFT_PAREN)
        s.pop(); //Removes LEFT PAREN FROM STACK -- CHECK BACK HERE IF SEGMENTATION FAULTS
}

void ShuntingYard::function_protocol(Queue<Token*>& q, Stack<Token*>& s, Token* t) {
    Function* o = static_cast<Function*>(t);
    s.push(o);
    cout << "is this a problem?" << endl;
}

void ShuntingYard::infix(Queue<Token*>& q) {
    my_queue = q;
}

Queue<Token*> ShuntingYard::postfix(Queue<Token*>& my_queue) {
    Stack<Token*> operators;
    Queue<Token*> post;
    Token* prev = nullptr;
    while(!my_queue.empty()) {
        Token* current = my_queue.pop();
        if(current->typeOf() == INTEGER /*|| current->typeOf() == FUNCTION*/) { //If stuff gets weird, probably this
            post.push(current);
        }
        else { //What about FUNCTION?
            if(current->typeOf() == RIGHT_PAREN) {
                paren_protocol(post, operators, current);
            }
            else if(current->typeOf() == OPERATOR) {
                if(operators.empty() && post.empty() && static_cast<Operator*>(current)->getVal() == MINUS) { //If stack and queue is empty, we know it's a unary op
                    operators.push(new Operator("u-"));
                }
                else if(prev != nullptr && static_cast<Operator*>(current)->getVal() == MINUS && (prev->typeOf() == OPERATOR || prev->typeOf() == LEFT_PAREN)) {
                    operators.push(new Operator("u-")); //If stack and queue are NOT empty, we need to check for previous token to deterimine if its unary
                }
                else {
                    operator_protocol(post, operators, current);
                }
            }
            // else if(current->typeOf() == FUNCTION){ //This wasn't working
            //     function_protocol(post, operators, current);
            //     //operators.push(current);
            // }
            else {
                operators.push(current);
            }
        }
        prev = current;
    }
    while(!operators.empty()) {
        Token* popped = operators.pop();
        post.push(popped);
    }
    return post;
}

Queue<Token*> ShuntingYard::postfix() {
    return postfix(my_queue);
}

ostream& operator<<(ostream& outs, ShuntingYard s) {
    Queue<Token*> q = s.my_queue;
    for(Queue<Token*>::Iterator it = q.begin(); it != q.end(); it++) {
        cout << *it;
    }
    return outs;
}