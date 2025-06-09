#include "sidebar.h"
#include "constants.h" // For SCREEN_HEIGHT
#include <iostream>   // Included via sidebar.h but good practice
#include <fstream>

Sidebar::Sidebar()
    : font(), sb_text(font), _left(0.f), _width(0.f), height(10.f), clearHistory(false) // initialize sb_text, provide defaults for _left, _width
{
    // this constructor is minimal. if it's actually used,
    // it would likely need to load the font and set up 'rect' as well.
    // for now, this makes it compile by initializing sb_text.
    std::cout << "Sidebar Default CTOR: Minimal initialization." << std::endl;

    for (int i = 0; i < 30; i++) //initializes items
    {
        items += ("");
    }
}

Sidebar::Sidebar(float left, float width)
    : font(), sb_text(font), _left(left), _width(width) // Initialize sb_text with font
{
    cout << "Sidebar CTOR: TOP" << endl;

    history.open("history.txt"); //Opens history.txt
    if(history.fail()) {
        historyMaker.open("history.txt");
        if(historyMaker.fail())
            exit(1);
    }

    // set up the sidebar rectangle:
    rect.setFillColor(sf::Color(192, 192, 192));  //silver
    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
    cout << "Sidebar CTOR: about to load font." << endl;

    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // the font file must be in the "working directory"
    //  check projects->run->working directory
    //       [Make sure it's not pointing to the app file]

    if (!font.openFromFile("Jokerman-Regular.ttf")) // SFML 3: openFromFile
    {
        cout << "Sidebar() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }
    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    cout << "Sidebar CTOR: loaded font." << endl;

    //. . . . . text / font problems: . . . . . . . .
    // sb_text is already constructed with 'font'. Now set its properties.
    // sb_text.setFont(font); // This is redundant as it was constructed with font.
    sb_text.setCharacterSize(20);
    sb_text.setStyle(sf::Text::Style::Bold); // SFML 3: sf::Text::Style::Bold
    sb_text.setFillColor(sf::Color(117, 0, 20));

    ////this is how you would position text on screen:
    // sb_text.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-sb_text.getLocalBounds().height-5));

    items += ("sidebar sample text");
    items += ("CLEAR LIST"); //Pushes back CLEAR LIST button
    // Fills the item vector with all the strings in the history.txt file
    for (int i = 0; i < 30; i++)
    {
        string eq;
        history >> eq;
        if(!eq.empty()) {
            cout << "yeah!" << endl;
            items += (eq);
        }
    }
    history.close();
    cout << "Sidebar: CTOR: Exit." << endl;
}

void Sidebar::resetItems() { //Removes all the equations in items
    int i = items.size()-1;
    while(i > 1) { //i must be greater than 1 because there are two items that are never popped: cursor coords and Clear LIst
        items.pop_back();
        i--;
    }
}

void Sidebar::update() { //Updates items vector whenver new equations are entered
    int historyLen = 1; //Records lengths of lines in history
    history.open("history.txt"); //Opens history to read from file
    if(history.fail()) {
        cout << "update failed" << endl;
        historyMaker.open("history.txt");
        if(historyMaker.fail())
            exit(1);
    }
    string eq;
    for(int i = 1; i <= items.size()+1; i++) {
        history >> eq; //Cycles through all the old equations in history.txt until it lands on the last line
        historyLen++; //Increments every time we read a function
        if(history.eof()) //If we are at at the end of the file, break
            break;
    }
    if(!eq.empty() && historyLen > items.size()) { 
        //If the last equation we read is not blank, and if historyLen is longer than items.size(), push back
        cout << "yeah!" << endl;
        items += (eq);
    }
    history.close();
    //close history
}

void Sidebar::draw(sf::RenderWindow &window)
{
    const double VERTICAL_LINE_SPACING = 5.0;
    const double LEFT_MARGIN = 10.0;
    //update();
    height = 10.f;

    int index = 0; //Index to increment for number of floatRect

    window.draw(rect);
    //float height = 10.f; // Use f for float literal
    for (int i = 0; i < items.size(); i++)
    {
        bool blank = false;
        if (items[i].size() == 0)
        {
            blank = true;
            sb_text.setString("BLANK");
        }
        else
        {
            sb_text.setString(items[i].c_str());
        }
        sb_text.setPosition(sf::Vector2f(_left + static_cast<float>(LEFT_MARGIN), height));

        //Increments height of where sb_text should be
        height += sb_text.getLocalBounds().size.y + static_cast<float>(VERTICAL_LINE_SPACING);

        //If the number of floatRects are less than the number of string items, and if the index exceeds the size of entryBounds,
        //We know we need to add a new floatRect
        if(entryBounds.size() < items.size() && index >= entryBounds.size()) {
                cout << sb_text.getGlobalBounds().position.x << ", " << sb_text.getGlobalBounds().position.y << endl;
                entryBounds += (sb_text.getGlobalBounds());
        }
        index++;
        if (!blank)
            window.draw(sb_text);
    }
}

Vector<sf::FloatRect>& Sidebar::getEntryBounds() { //return vector of entryBounds for each floatRect
    return entryBounds;
}

string &Sidebar::operator[](int index)
{
    return items.at(index);
}