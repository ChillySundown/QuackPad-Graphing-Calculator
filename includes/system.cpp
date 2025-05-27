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


void System::Step(int command, GraphInfo* g) {
    //_graph.update(*g);
}

void System::Draw(sf::RenderWindow &window)
{
    Graph g;
    g.Draw(window);
    // // window.clear(); // this clear is redundant, animate::render() already clears.
    // for(int i = 0; i < system.size(); i++) {
    //     system[i].Draw(window);
    // }
}
