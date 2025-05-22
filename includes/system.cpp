#include "system.h"
#include "random.h"
#include "constants.h"
#include <iostream>
#include "particle.h"
#include "plot.h"
#include "graph.h"

System::System()
{
    system = vector<Particle>();
}

System::System(const vector<Particle>& p) {
    system = p;
}

System::System(GraphInfo* info) {
    _graph = Graph(info);
}

void System::set_info(GraphInfo* info) {
    _graph.set_info(info);
}

//------------------------------------------------------------------
//------------------------------------------------------------------

void System::Step(int command) {
    // for(int i = 0; i < system.size(); i++) {
    //     system[i].Step(command);
    // }
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

int System::Size()
{
    return system.size(); // Or 1 if it represents the single shape for now
}