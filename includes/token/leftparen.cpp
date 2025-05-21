#include <iostream>
#include <iomanip>
#include <cassert>
#include "leftparen.h"
#include "token.h"

LeftParen::LeftParen() {
    Token();
    my_left_paren = "(";
}

int LeftParen::typeOf() {
    return LEFT_PAREN;
}

void LeftParen::printToken() {
    cout << my_left_paren;
}




