#include "token.h"
#include <iostream>
#include <iomanip>

using namespace std;

Token::Token() {
    my_str = "";
}

Token::Token(string str) {
    my_str = str;
}

void Token::printToken() { //Will lack of ostream& variable be a problem?
    cout << my_str;
}

ostream& operator<<(ostream& outs, Token* t) {
    t->printToken();
    return outs;
}

int Token::typeOf() {
    return TOKEN;
}