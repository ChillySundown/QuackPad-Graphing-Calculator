#include "animate.h"
#include "constants.h"
#include "token/token.h"
#include <iostream>


animate::animate()
    : font(), myTextLabel(font), textBox(), sidebar(WORK_PANEL, SIDE_BAR)
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
    // system = System(); // system is already default-constructed as a member
    // vector<Particle> container;
    // Random r;
    // int num_particles = r.Next(10, 40);
    // for(int i = 0; i < num_particles; i++) {
    //     container.push_back(Particle());
    // }
    // system = System(container);
    window.setFramerateLimit(60);

    textBox.setSize(sf::Vector2f(SIDE_BAR + 15.f, 30.f));
    textBox.setFillColor(sf::Color::Transparent);
    textBox.setPosition(sf::Vector2f(0.f, SCREEN_HEIGHT - 30.f));

    //Our goat GraphInfo!!!
    info = new GraphInfo();
    //system = System(info); Makes the x axis disappear for some reason;
    //cout << "What a pain!";

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
    system.Draw(window);
    window.draw(textBox);
    if (mouseIn)
    {
        window.draw(mousePoint);
    }
    
    sidebar.draw(window);
    //- - - - - - - - - - - - - - - - - - -
    // getPosition() gives you screen coords, getPosition(window) gives you window coords
    // cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -
    // drawing Test: . . . . . . . . . . . .
    // This is how you draw text:)
    window.draw(myTextLabel);
    //. . . . . . . . . . . . . . . . . . .
}

void animate::update()
{
    // cause changes to the data for the next frame
    system.Step(command, info); //REMINDER --- YOU NEED THIS! THIS SPECIFICALLY REMEMBER TO UNCOMMENT
    command = 0;
    sidebar.update();
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
    myTextLabel.setString(input);
    //info->set_x(0, 10); //WE CAN NOW DYNAMICALLY ALTER THE GRAPH!!!

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
                //sidebar[SB_KEY_PRESSED] = "LEFT ARROW";
                command = 4;
                system.Step(command, info);
                break;
            case sf::Keyboard::Key::Right: // SFML 3: sf::Keyboard::Key::Right
                //sidebar[SB_KEY_PRESSED] = "RIGHT ARROW";
                command = 6;
                system.Step(command, info);
                break;
            case sf::Keyboard::Key::Escape: // SFML 3: sf::Keyboard::Key::Escape
                //sidebar[SB_KEY_PRESSED] = "ESC: EXIT";
                window.close();
                break;
            case sf::Keyboard::Key::Equal: //Zooms into the graph
                if(!info->getInputStatus()) {
                    command = 8;
                    system.Step(command, info);
                }
                break;
            case sf::Keyboard::Key::Hyphen:
                if(!info->getInputStatus()) {
                    command = 9;
                    system.Step(command, info);
                }
                break;
            case sf::Keyboard::Key::Backslash:
                command = 2;
                info->setInputStatus(!info->getInputStatus());
                if(info->getInputStatus()) {
                    textBox.setFillColor(sf::Color::White);
                }
                else {
                    textBox.setFillColor(sf::Color::Transparent);
                }
                break;
                //system.Step(command, info);
            case sf::Keyboard::Key::Enter:
                history.open("history.txt", ios::app);
                if(history.fail()) {
                    cout << "WAHHHHEIIUH HOWCOULDYOUUU" << endl;
                    exit(1);
                }
                command = 5;
                cout << "Submitted!" << endl;
                try {
                    info->setEquation(input);
                    history << input << "\n";
                    input = "";

                    //sidebar.update();

                    info->setInputStatus(false);
                    textBox.setFillColor(sf::Color::Transparent);
                } catch(exception e) {
                    input = "Invalid equation";
                }
                history.close();
                break;
            case sf::Keyboard::Key::P:
                info->togglePolar();
            default: //For equation input, process it in another function (Crashes when in processEvents)
                break;
            }
        }
        else if(const auto textEntered = event.getIf<sf::Event::TextEntered>()) {
            if(textEntered->unicode < 128) {
                if(!input.empty() && textEntered->unicode == 8) {
                    input.pop_back();
                }
                else if(info->getInputStatus() && !(textEntered->unicode == 8 || textEntered->unicode == 92)) {
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
            vector<sf::FloatRect> history_entries = sidebar.getEntryBounds();
            mouseX = static_cast<float>(mouseMoved->position.x); // position is sf::Vector2i
            mouseY = static_cast<float>(mouseMoved->position.y);
            //cout << history_entries.size() << endl;
            //sf::FloatRect s = history_entries.at(0);
            // for(int i = 0; i < history_entries.size(); i++) {
            //     if(history_entries[i].contains(sf::Vector2f(mouseX, mouseY))) {
            //         cout << sidebar[i] << endl;
            //     }   
            // }
            // do something with it if you need to...
        }
        else if (const sf::Event::MouseButtonReleased* mouseButton = event.getIf<sf::Event::MouseButtonReleased>())
        {
            vector<sf::FloatRect> history_entries = sidebar.getEntryBounds();
            if (mouseButton->button == sf::Mouse::Button::Left) // SFML 3: sf::Mouse::Button::Right
            {
                for(int i = 0; i < history_entries.size(); i++) {
                    if(history_entries[1].contains(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))) {
                        cout << "clear it out!" << endl;
                        try {
                            history.open("history.txt");
                            if(history.fail()) {
                                exit(1);
                            }
                            sidebar.resetItems();
                            history.close();
                        } catch(exception e) {
                            cout << "Don't double click!" << endl;
                        }
                        break;
                    }
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