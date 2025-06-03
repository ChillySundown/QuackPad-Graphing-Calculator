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
    float new_x_min = g->get_x_min() + 2;
    float new_x_max = g->get_x_max() - 2;

    float new_y_min = g->get_y_min() + 2;
    float new_y_max = g->get_y_max() - 2;

    //g->set_x()
}

void System::Step(int command, GraphInfo* g) {
    //set_info(g);
    if(command == 1) {
        //zoom(g);
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
