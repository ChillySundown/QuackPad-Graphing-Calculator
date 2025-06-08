#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;


class Sidebar
{
public:
    Sidebar();
    Sidebar(float left, float width);
    void draw(sf::RenderWindow& window);
    vector<sf::FloatRect>& getEntryBounds();
    string& operator [](int index);
    void update();
private:
    sf::RectangleShape rect;            //sidebar rectangle
    vector<string> items;               //strings to place on the sidebar
    vector<sf::FloatRect> entryBounds;
    sf::Font font;                      //used to draw text // Ensure declared before sb_text
    sf::Text sb_text;                   //used to draw strings on the window object
    ifstream history;

    float _left;
    float _width;

};

#endif // SIDEBAR_H