#include <iostream>
#include <iomanip>
#include <cassert>
#include "token.h"
#include "rightparen.h"

RightParen::RightParen() {
    Token();
    my_right_paren = ")";
}

int RightParen::typeOf() {
    return RIGHT_PAREN;
}

void RightParen::printToken() {
    cout << my_right_paren;
}
