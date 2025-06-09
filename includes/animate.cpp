#include "animate.h"
#include "constants.h"
#include "token/token.h"
#include <iostream>


animate::animate()
    : font(), myTextLabel(font), textBox(), sidebar(WORK_PANEL, SIDE_BAR), helpTab(), myHelpLabel(font)
{
    cout << "animate CTOR: TOP" << endl;
    // SFML 3: VideoMode constructor takes sf::Vector2u or {unsigned int, unsigned int}
    window.create(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "ACME Graphing Calculator");
    // VideoMode class has functions to detect screen size etc.
    // RenderWindow constructor has a third argumnet to set style
    // of the window: resize, fullscreen etc.

    // System will be implemented to manage a vector of objects to be animated.
    //   at that point, the constructor of the System class will take a vector
    //   of objects created by the animate object.
    //   animate will
    window.setFramerateLimit(60);


    //sets help tab size, color, and position)
    helpTab.setSize(sf::Vector2f(30, 60));
    helpTab.setOutlineThickness(2.f);
    helpTab.setFillColor(sf::Color::Transparent);
    helpTab.setOutlineColor(sf::Color::Transparent);
    helpTab.setSize(sf::Vector2f(300, 250));
    helpTab.setPosition(sf::Vector2f(50, 50));

    //set help text size, color, and position
    myHelpLabel.setString("Help:\nPlus Key: Zoom In\nMinus Key: Zoom Out\nLeft Arrow: Pan Left\nRight Arrow: Pan Right\nBackslash: Toggle User Input\nEnter: Submit Equation\nP: Toggle Polar");
    myHelpLabel.setCharacterSize(20);
    myHelpLabel.setStyle(sf::Text::Style::Regular);
    myHelpLabel.setFillColor(sf::Color::Transparent);
    myHelpLabel.setPosition(helpTab.getPosition());

    //Sets size, color, and position of user input textBox.
    textBox.setSize(sf::Vector2f(SIDE_BAR + 15.f, 30.f)); 
    textBox.setFillColor(sf::Color::Transparent);
    textBox.setPosition(sf::Vector2f(0.f, SCREEN_HEIGHT - 30.f));

    //Our goat GraphInfo!!!
    info = new GraphInfo();

    mouseIn = true;

    mousePoint = sf::CircleShape(); // default constructed, then set properties
    mousePoint.setRadius(5.0f);     // use f for float literal
    mousePoint.setFillColor(sf::Color::Red);

    cout << "Game CTOR. preparing to load the font." << endl; // Typo: Geme -> Game
    //--- FONT ----------
    // font file must be in the "working directory:
    //      debug folder
    // Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    // font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.openFromFile("Jokerman-Regular.ttf")) // SFML 3: openFromFile
    {
        cout << "animate() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }

    // myTextLabel is already constructed with font. now set its properties.
    // myTextLabel = sf::Text("Initial String for myTextLabel", font); // This was assignment + wrong constructor
    myTextLabel.setString("ACME Graphing Calculator");
    // myTextLabel.setFont(font); // Redundant, already constructed with font
    myTextLabel.setCharacterSize(25);
    myTextLabel.setStyle(sf::Text::Style::Regular); // SFML 3: sf::Text::Style::Bold
    myTextLabel.setFillColor(sf::Color::Black);
    // assuming .height is correct for SFML 3. Use .f for float literals.
    myTextLabel.setPosition(textBox.getPosition());
    cout << "animate instantiated successfully." << endl;
}

void animate::Draw()
{
    //Draws the new graph depending on GraphInfo
    system.Draw(window);
    //Draws myHelpLabel on helpTab
    window.draw(myHelpLabel);
    //Draws textBox inside of graph
    window.draw(textBox);
    //Draws helpTab
    window.draw(helpTab);
    if (mouseIn)
    {
        window.draw(mousePoint);
    }
    
    //Draws sidebar and all the textLabels inside
    sidebar.draw(window);
    //Draws the userInput text as its getting typed in
    window.draw(myTextLabel);

    //. . . . . . . . . . . . . . . . . . .
}

void animate::update()
{
    // cause changes to the data for the next frame
    system.Step(command, info);
    command = 0;
    sidebar.update(); //Updtates the history in sidebar by reading the text file
    if (mouseIn)
    {
        // mousePoint red dot:
        // sf::Mouse::getPosition returns sf::Vector2i. setPosition prefers sf::Vector2f or float, float.
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        mousePoint.setPosition({static_cast<float>(mousePos.x - 5),
                               static_cast<float>(mousePos.y - 5)});

        // mouse location text for sidebar:
        sidebar[SB_MOUSE_POSITION] = mouse_pos_string(window);
    }
    myTextLabel.setString(input); //Sets the updated input string to the textBox after each key is pressed

}
void animate::render()
{
    window.clear();
    Draw();
    window.display();
}

animate::~animate() { //Destructor for GraphInfo pointer
    delete info;
}

void animate::processEvents()
{
    // sf::Event event;
    float mouseX, mouseY;
    // SFML 3: pollEvent returns std::optional<sf::Event>
    while (auto optEvent = window.pollEvent())
    {
        sf::Event event = *optEvent; // get the event from the optional
        

        /*****
         For text input, use the TextEntered event, and only append characters that have a unicode under 128
         ******/

        // check the type of the event...
        if (event.is<sf::Event::Closed>())
        {
            window.close();
        }
        else if (const sf::Event::KeyPressed* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            switch (keyPressed->code)
            {
            case sf::Keyboard::Key::Left: // SFML 3: sf::Keyboard::Key::Left
                command = 4;
                system.Step(command, info);
                break;
            case sf::Keyboard::Key::Right: // SFML 3: sf::Keyboard::Key::Right
                command = 6;
                system.Step(command, info);
                break;
            case sf::Keyboard::Key::Escape: // SFML 3: sf::Keyboard::Key::Escape
                window.close();
                break;
            case sf::Keyboard::Key::Equal: //Zooms into the graph
                if(!info->getInputStatus()) { //If graph is NOT accepting input, zoom in
                    command = 8; 
                    system.Step(command, info); //Handles domain math when zooming in
                }
                break;
            case sf::Keyboard::Key::Hyphen: //Zooms out of graph
                if(!info->getInputStatus()) { //If graph is NOT accepting input, zoom out
                    command = 9; 
                    system.Step(command, info); //Handles domain math when zooming out
                }
                break;
            case sf::Keyboard::Key::Backslash: //Activates user input
                command = 2;
                info->setInputStatus(!info->getInputStatus()); //Toggles user input status
                if(info->getInputStatus()) { //If taking input, set textBox to visible
                    textBox.setFillColor(sf::Color::White);
                }
                else { //Otherwise, textBox is transparent
                    textBox.setFillColor(sf::Color::Transparent);
                }
                break;
            case sf::Keyboard::Key::Enter: //Writes the input string to the text file and sets the input string as the equation in the graph
                history.open("history.txt", ios::app); //Opens the file to append input string
                if(history.fail()) { //Failure protocol
                    cout << "Failed input append in history.txt" << endl;
                    exit(1);
                }
                command = 5;
                try {
                    info->setEquation(input); ///Sets GraphInfo equation to input equation
                    history << input << "\n"; //Writes equation to history.txt
                    input = ""; //Clears input string

                    info->setInputStatus(false); //Set input status to false
                    textBox.setFillColor(sf::Color::Transparent); //Set textBox to transparent
                } catch(exception e) {
                    input = "Invalid equation"; //If input is faulty, informs user that equation is invalid.
                }
                history.close(); //Closes history.txt
                break;
            case sf::Keyboard::Key::P:
                if(!info->getInputStatus())
                    info->togglePolar(); //Toggles Polar coordinates
                break;
            case sf::Keyboard::Key::F1:
                if(helpTab.getOutlineColor() == sf::Color::Transparent) {
                    helpTab.setOutlineColor(sf::Color::White);
                    myHelpLabel.setFillColor(sf::Color::White);
                }
                else {
                    helpTab.setOutlineColor(sf::Color::Transparent);
                    myHelpLabel.setFillColor(sf::Color::Transparent);
                }
                break;
            default: 
                break;
            }
        }
        else if(const auto textEntered = event.getIf<sf::Event::TextEntered>()) { //Handles user input
            if(textEntered->unicode < 128) {
                if(!input.empty() && textEntered->unicode == 8) {  //Backspace
                    input.pop_back();
                }
                else if(info->getInputStatus() && !(textEntered->unicode == 8 || textEntered->unicode == 92)) { //If system takes user input and if not backspace or backslash, append to input str
                    input += static_cast<char>(textEntered->unicode);
                }
            }
        } 
        else if (event.is<sf::Event::MouseEntered>())
        {
            mouseIn = true;
        }
        else if (event.is<sf::Event::MouseLeft>())
        {
            mouseIn = false;
        }
        else if (const sf::Event::MouseMoved* mouseMoved = event.getIf<sf::Event::MouseMoved>())
        {
            mouseX = static_cast<float>(mouseMoved->position.x); // position is sf::Vector2i
            mouseY = static_cast<float>(mouseMoved->position.y);
            // do something with it if you need to...
        }
        else if (const sf::Event::MouseButtonReleased* mouseButton = event.getIf<sf::Event::MouseButtonReleased>())
        {
            Vector<sf::FloatRect> history_entries = sidebar.getEntryBounds(); //Returns a vector of FloatRec that contain each of the entries in history
            if (mouseButton->button == sf::Mouse::Button::Left) // SFML 3: sf::Mouse::Button::Left
            {
                for(int i = 0; i < history_entries.size(); i++) { //Loops through Floatrec vector of entries
                    //Checks to see if the mouse is hovering over the CLEAR button
                    if(history_entries[1].contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))) {
                        try { //Opens history file to clear and clears vector of equation strings
                            history.open("history.txt");
                            if(history.fail()) {
                                exit(1);
                            }
                            sidebar.resetItems();
                            history.close();
                        } catch(exception e) {
                            //Ignores request
                        }
                        break;
                    }
                    //If the mouse is hovering over one of our equations in the history, it sets that equation by updating GraphInfo
                    else if(i != 0 && history_entries[i].contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))) {
                        cout << "setting new equation" << endl;
                        info->setEquation(sidebar[i]);
                    }  
                }
            }
            else // assuming other clicks are left, or check sf::Mouse::Button::Left
            {
                // sidebar[SB_MOUSE_CLICKED] = "LEFT CLICK " +
                //                             mouse_pos_string(window);
            }
        }

    }
}
void animate::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render(); // clear/draw/display
    }
    cout << endl
         << "-------ANIMATE MAIN LOOP EXITING ------------" << endl;
}


std::string mouse_pos_string(sf::RenderWindow &window)
{
    return "(" +
           std::to_string(sf::Mouse::getPosition(window).x) +
           ", " +
           std::to_string(sf::Mouse::getPosition(window).y) +
           ")";
}