#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "../includes/vector/vector.h"
#include <fstream>
#include <cstdlib>
using namespace std;


class Sidebar
{
public:
    Sidebar();
    Sidebar(float left, float width);
    void draw(sf::RenderWindow& window);
    Vector<sf::FloatRect>& getEntryBounds();
    void resetItems();
    string& operator [](int index);
    void update();
private:
    sf::RectangleShape rect;            //sidebar rectangle
    Vector<string> items;               //strings to place on the sidebar
    Vector<sf::FloatRect> entryBounds;
    sf::Font font;                      //used to draw text // Ensure declared before sb_text
    sf::Text sb_text;                   //used to draw strings on the window object
    ifstream history;                   //used to read input from our history
    ofstream historyMaker;              //used in case Barkeshli decides to delete our history
    bool clearHistory;                  //Bool flag that tells us to clear history

    float _left;
    float _width;
    float height;

};

#endif // SIDEBAR_H