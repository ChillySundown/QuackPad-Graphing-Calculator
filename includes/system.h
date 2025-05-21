#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include "particle.h"
#include <SFML/Graphics.hpp>

using namespace std;
class System
{
public:
    System();
    System(const vector<Particle>& p);
    void Step(int command);
    int Size();
    void Draw(sf::RenderWindow& widnow);
private:
    vector<Particle> system;
};

#endif // SYSTEM_H
