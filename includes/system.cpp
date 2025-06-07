#include "system.h"
#include "random.h"
#include "constants.h"
#include <iostream>
#include "particle.h"
#include "plot.h"
#include "graph.h"


System::System()
{

}


System::System(GraphInfo* info) {
    _graph = Graph(info);
}

void System::set_info(GraphInfo* info) { //Update does everything anyway.
    _graph.set_info(info);
}

//------------------------------------------------------------------
//------------------------------------------------------------------

void System::ZoomIn(GraphInfo* g) {
    float new_x_min = g->get_x_min() + 0.8f;
    float new_x_max = g->get_x_max() - 0.8f;

    float new_y_min = g->get_y_min() + 0.8f;
    float new_y_max = g->get_y_max() - 0.8f;

    g->set_x(new_x_min, new_x_max);
    g->set_y(new_y_min, new_y_max);
}

void System::ZoomOut(GraphInfo* g) {
    float new_x_min = g->get_x_min() - 0.8f;
    float new_x_max = g->get_x_max() + 0.8f;

    float new_y_min = g->get_y_min() - 0.8f;
    float new_y_max = g->get_y_max() + 0.8f;

    g->set_x(new_x_min, new_x_max);
    g->set_y(new_y_min, new_y_max);
}

void System::PanLeft(GraphInfo* g) {
    float new_x_min = g->get_x_min() - 1;
    float new_x_max = g->get_x_max() - 1;

    g->set_x(new_x_min, new_x_max);
}

void System::PanRight(GraphInfo* g) {
    float new_x_min = g->get_x_min() + 1;
    float new_x_max = g->get_x_max() + 1;

    g->set_x(new_x_min, new_x_max);
}

void System::Step(int command, GraphInfo* g) {
    //set_info(g);
    if(command == 4) {
        PanLeft(g);
    }
    if(command == 6) {
        PanRight(g);
    }
    if(command == 8) {
        ZoomIn(g);
    }
    if(command == 9) {
        ZoomOut(g);
    }
    if(command == 2) {
        g->setInputStatus(true);
        // string eq;
        // cin >> eq;
        //g->setEquation(eq);
    }
    _graph.update(g);
}

void System::Draw(sf::RenderWindow &window)
{
    _graph.Draw(window);
    // // window.clear(); // this clear is redundant, animate::render() already clears.
    // for(int i = 0; i < system.size(); i++) {
    //     system[i].Draw(window);
    // }
}
