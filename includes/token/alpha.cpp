#include "alpha.h"
#include "token.h"

#include <iostream>
#include <iomanip>

Alpha::Alpha() : Token(), my_char('\0'){
}

Alpha::Alpha(char c) : Token(), my_char(c) {

}

void Alpha::printToken() {
    cout << my_char;
}

int Alpha::typeOf() {
    return 999; //Remember this!!
 }
