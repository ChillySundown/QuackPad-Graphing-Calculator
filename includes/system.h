#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include "particle.h"
#include "graph_info.h"
#include "graph.h"
#include <SFML/Graphics.hpp>

using namespace std;
class System
{
public:
    System();
    System(const vector<Particle>& p);

    System(GraphInfo* info); //Do we need this?

    void set_info(GraphInfo* info);

    void Step(int command, GraphInfo* g);
    int Size();
    void Draw(sf::RenderWindow& widnow);
private:
    vector<Particle> system; 
    Graph _graph;
};

#endif // SYSTEM_H
