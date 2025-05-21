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

//------------------------------------------------------------------
//------------------------------------------------------------------

void System::Step(int command) {
    // for(int i = 0; i < system.size(); i++) {
    //     system[i].Step(command);
    // }
}

void System::Draw(sf::RenderWindow &window)
{
    Plot p;
    Graph g(p);
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