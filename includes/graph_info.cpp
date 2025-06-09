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
GraphInfo::GraphInfo() { 
    _max_x_screen = SCREEN_WIDTH;
    _max_y_screen = SCREEN_HEIGHT;
    _x_min = -5; //Default graph mins/maxes
    _x_max = 5;
    _y_min = -5;
    _y_max = 5;
    inputStatus = false; //Users must click "\" to activate input
    polar = false; //Cartesian coords are default
    _points = 600; //Definition

}

/******
 * ACCESSORS
 */

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

bool GraphInfo::getInputStatus() {
    return inputStatus;
}

/*********
 * MODIFIERS
 */
 
void GraphInfo::set_x(float x_min, float x_max) {
    _x_min = x_min;
    _x_max = x_max;
}
void GraphInfo::set_y(float y_min, float y_max) {
    _y_min = y_min;
    _y_max = y_max;
}

void GraphInfo::setInputStatus(bool status) {
    inputStatus = status;
}


/*****
 * HELPER FUNCTIONS FOR TOKENIZER
 */

bool bothNumbers(char c1, char c2) { //Checks to see if both characters are numbers
    char c1Val = c1 - 48; //Reduces character to integer vals
    char c2Val = c2 - 48;
    if(c1Val >= 0 && c1Val <= 9 && c2Val >= 0 && c2Val <= 9) {
        return true;
    }
    return false;
}

bool bothLetters(char c1, char c2) { //Checks to see if both characters are lowercase letters
    char c1Val = c1 - 97;   //Strips down characters to lowercase letters
    char c2Val = c2 - 97;
    if(c1Val >= 0 && c1Val <= 25 && c2Val >= 0 && c2Val <= 25) {
        return true;
    }
    return false;
}

void str_spacer(string& s) { //Iterates through string and spaces out tokenizable portions
    for(int i = 0; i < s.size()-1; i++) {
        char c1 = s.at(i); //Walker 1
        char c2 = s.at(i+1); //Walker 2
        if(!bothNumbers(c1, c2) && !bothLetters(c1, c2) && c1 != '.' && c2 != '.') {
            //If both characters are NOT numbers or letters and neither one is a decimal point, then insert a space and increase size
            s.insert(i+1, " ");
            i++;
        }
    }
}

bool GraphInfo::isPolar() { //Accessor for Polar coords
    return polar;
}

void GraphInfo::togglePolar() { //Toggles polar
    polar = !polar;
}

/******
 * POSTCONDITION - Output is a Queue of token* that can be evaluated to a valid expression by the ShuntingYard/RPN algorithm
 * 
 */
Queue<Token*> GraphInfo::tokenizer(string expression) {
    Queue<Token*> token_queue;
    str_spacer(expression); //Spaces out our expression

    string strToken; //Declares strToken string that will be used to evaluate each token in the expression

    /*****
     * This part initializes an cstring equal to the spaced out expression
     * We convert to a c-string for compatibility with the strtok function
     */
    char* exp = new char[expression.size()+1]; 
    strcpy(exp, expression.c_str());

    char* tokens = strtok(exp, " "); //Separates the cstring into individual string tokens whenver it encounters a space

    while(tokens != NULL) { //While there are still tokens in the array
        strToken = string(tokens); //Converts token cstring back into a string

        //Checks to see if stToken is variable
        if(strToken == "x" || strToken == "sin" || strToken == "cos" || strToken == "tan" || strToken == "arccos" || strToken == "arcsin" || strToken == "arctan" || strToken == "pi") {
            token_queue.push(new Function(strToken));
        }
        else if(strToken == "+" || strToken == "-" || strToken == "*" || strToken == "/" || strToken == "^") { //Checks if strToken is Operator
            token_queue.push(new Operator(strToken));
        }
        else if(strToken == "(") { //Checks if strToken is LeftParen
            token_queue.push(new LeftParen());
        }
        else if(strToken == ")") { //Checks if strToken is RightParen
            token_queue.push(new RightParen());
        }
        else { //Otherwise, converts token to number and pushes to token_queue
            token_queue.push(new Integer(stof(strToken)));
        }
        tokens = strtok(NULL, " "); //Moves to next token
    }
    return token_queue;
}

void GraphInfo::setEquation(string eq) {
    Queue<Token*> t = tokenizer(eq); //Tokenizes equation
    _q = t;
}

Queue<Token*>& GraphInfo::get_expression() { //Returns a queue of the expression
    return _q;
}