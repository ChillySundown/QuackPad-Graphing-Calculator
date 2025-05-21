#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <iomanip>
#include "random.h"
#include "constants.h"
#include <SFML/Graphics.hpp>

class Particle {
    public:
        Particle();
        Particle(sf::Vector2f pos);
        void Step(int command);
        void Draw(sf::RenderWindow& widnow);
    private:
        //sf::CircleShape _shape;
        float _radius;
        sf::Vector2f _pos;
        sf::Vector2f _vel;
        sf::Color _fill_color;
        

};
#endif