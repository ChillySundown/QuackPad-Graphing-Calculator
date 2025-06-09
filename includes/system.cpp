#include "system.h"
#include "random.h"
#include "constants.h"
#include <iostream>
#include "particle.h"
#include "plot.h"
#include "graph.h"


System::System() //Default constructor
{
//Look at me, I'm a cute comment :)
}


System::System(GraphInfo* info) { //Initializes Graph object with GraphInfo pointer
    _graph = Graph(info);
}

void System::set_info(GraphInfo* info) { //Update does everything anyway.
    _graph.set_info(info);
}

//------------------------------------------------------------------
//------------------------------------------------------------------

void System::ZoomIn(GraphInfo* g) { //Makes x-axis and y-axis smaller by 0.8f on all sides
    float new_x_min = g->get_x_min() + 0.8f;
    float new_x_max = g->get_x_max() - 0.8f;

    float new_y_min = g->get_y_min() + 0.8f;
    float new_y_max = g->get_y_max() - 0.8f;

    g->set_x(new_x_min, new_x_max); //Updates the GraphInfo pointer
    g->set_y(new_y_min, new_y_max);
}

void System::ZoomOut(GraphInfo* g) { //Makes x-axis and y-axis bigger by 0.8f on all sides
    float new_x_min = g->get_x_min() - 0.8f;
    float new_x_max = g->get_x_max() + 0.8f;

    float new_y_min = g->get_y_min() - 0.8f;
    float new_y_max = g->get_y_max() + 0.8f;

    g->set_x(new_x_min, new_x_max);
    g->set_y(new_y_min, new_y_max); //Updates the GraphInfo pointer
}

void System::PanLeft(GraphInfo* g) { //Shifts x-min and x-max left by 1.f
    float new_x_min = g->get_x_min() - 1;
    float new_x_max = g->get_x_max() - 1;

    g->set_x(new_x_min, new_x_max); //Updates x-min and x-max
}

void System::PanRight(GraphInfo* g) { //Shifts x-min and x-max right by 1.f
    float new_x_min = g->get_x_min() + 1;
    float new_x_max = g->get_x_max() + 1;

    g->set_x(new_x_min, new_x_max); //Updates x-min and x-max
}

void System::Step(int command, GraphInfo* g) { //Updates Graph based off keystrokes from user input
    if(command == 4) { //LEFT-ARROW
        PanLeft(g);
    }
    if(command == 6) { //RIGHT-ARROW
        PanRight(g);
    }
    if(command == 8) { //EQUALS (PLUS) KEY
        ZoomIn(g);
    }
    if(command == 9) { //HYPHEN (MINUS) KEY
        ZoomOut(g);
    }
    _graph.update(g);
}

void System::Draw(sf::RenderWindow &window)
{
    _graph.Draw(window); //Draws the window
}
