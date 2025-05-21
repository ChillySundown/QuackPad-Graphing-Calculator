#include <iostream>
#include <iomanip>
#include "../includes/animate.h"
#include "../includes/system.h"
#include "../includes/random.h"
#include <SFML/Graphics.hpp>


using namespace std;

int main(int argv, char** argc) {
    animate game;
    game.run();
    cout << "\n\n"
         << endl;

    cout << "\n\n\n=====================" << endl;
    return 0;
}
