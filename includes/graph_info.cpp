#include "graph_info.h"
#include "constants.h"
#include "../includes/stack/MyStack.h"
#include "../includes/queue/MyQueue.h"
#include "token/token.h"
#include "token/function.h"
#include "token/integer.h"
#include "token/operator.h"
#include "token/leftparen.h"
#include "token/rightparen.h"
GraphInfo::GraphInfo() { //You need to make polar coords
    _max_x_screen = SCREEN_WIDTH;
    _max_y_screen = SCREEN_HEIGHT;
    _x_min = -10;
    _x_max = 10;
    _y_min = -10;
    _y_max = 10;
    _q.push(new Function("sin"));
    _q.push(new LeftParen());
    _q.push(new Function("x"));
    _q.push(new RightParen());
    _points = 300;
    // _window_dimensions = sf::Vector2f(600.f, 600.f);
    // _origin = sf::Vector2f(300.f, 300.f);
    // _domain = sf::Vector2f(-5.f, 5.f);
    // _equation = "x";

}

GraphInfo::GraphInfo(float x_screen, float y_screen, float x_min, float x_max, float y_min, float y_max, Queue<Token*> q) {
    _max_x_screen = x_screen;
    _max_y_screen = y_screen;
    _x_min = x_min;
    _x_max = x_max;
    _y_min = y_min;
    _y_max = y_max;
    _q = q;
}

float GraphInfo::get_x_screen() {
    return _max_x_screen;
}
float GraphInfo::get_y_screen() {
    return _max_y_screen;
}
float GraphInfo::get_x_min() {
    return _x_min;
}
float GraphInfo::get_x_max() {
    return _x_max;
}
float GraphInfo::get_y_min() {
    return _y_min;
}
float GraphInfo::get_y_max() {
    return _y_max;
}

int GraphInfo::getNumPoints() {
    return _points;
}

void GraphInfo::set_x(float x_min, float x_max) {
    _x_min = x_min;
    _x_max = x_max;
}
void GraphInfo::set_y(float y_min, float y_max) {
    _y_min = y_min;
    _y_max = y_max;
}

bool bothNumbers(char c1, char c2) {
    char c1Val = c1 - 48;
    char c2Val = c2 - 48;
    if(c1Val >= 0 && c1Val <= 9 && c2Val >= 0 && c2Val <= 9) {
        return true;
    }
    return false;
}

bool bothLetters(char c1, char c2) {
    char c1Val = c1 - 97;
    char c2Val = c2 - 97;
    if(c1Val >= 0 && c1Val <= 25 && c2Val >= 0 && c2Val <= 25) {
        return true;
    }
    return false;
}

void str_spacer(string& s) {
    for(int i = 0; i < s.size()-1; i++) {
        char c1 = s.at(i);
        char c2 = s.at(i+1);
        if(!bothNumbers(c1, c2) && !bothLetters(c1, c2) && c1 != '.' && c2 != '.') {
            s.insert(i+1, " ");
            i++;
        }
        // else 
        // else {
        //     s.insert(i+1, " ");
        //     i++;
        // }
        //cout << s << endl;
    }
}

//PRECONDITION: EXPRESSION HAS BEEN SPACED OUT
Queue<Token*> GraphInfo::tokenizer(string expression) {
    Stack<Token*> token_stack;
    str_spacer(expression);
    int i = 0;
    string strToken;

    char* exp = new char[expression.size()+1];
    strcpy(exp, expression.c_str());

    char* tokens = strtok(exp, " ");
    while(tokens != NULL) {
        strToken = string(tokens);
        
    }

    }
    // while(!expression.empty()) {
    //     char popped = expression.back(); //What about decimals????
    //     if(popped < 10) {
    //         token_stack.push(new Integer(popped));
    //     }
    //     else {
    //         string only_char;
    //         only_char += popped;
    //         if(popped == '+' || popped == '-' || popped == '/' || popped == '^') {
    //             token_stack.push(new Operator(only_char));
    //         }
    //         else if(popped == '(') {
    //             token_stack.push(new LeftParen());
    //         }
    //         else if(popped == ')') {
    //             token_stack.push(new RightParen());
    //         }
    //     }
    // }
    return Queue<Token*>();
}

Queue<Token*>& GraphInfo::get_expression() {
    return _q;
}