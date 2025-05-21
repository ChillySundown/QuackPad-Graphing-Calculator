#include "particle.h"
#include "random.h"
#include "constants.h"

Particle::Particle() {
    Random rand;

    int xpos = rand.Next(50, 100);
    int ypos = rand.Next(50, 100);

    _radius = static_cast<float>(rand.Next(8, 25));

    //_shape = sf::CircleShape(_radius);
    _pos = sf::Vector2f(static_cast<float>(xpos), static_cast<float>(ypos));
    _vel = sf::Vector2f(static_cast<float>(rand.Next(-10, 10)), static_cast<float>(rand.Next(-10, 10)));

    int _r = rand.Next(0, 255);
    int _g = rand.Next(0, 255);
    int _b = rand.Next(0, 255);

    _fill_color = sf::Color(static_cast<uint32_t>(_r), static_cast<uint32_t>(_g), static_cast<uint32_t>(_b));
}

Particle::Particle(sf::Vector2f pos) {
    _pos = pos;
    _radius = 5.f;
    _fill_color = sf::Color(static_cast<uint32_t>(200), static_cast<uint32_t>(0), static_cast<uint32_t>(0));
}

void Particle::Step(int command) {
    //_shape.move(_vel);

    float diameter = 2.f * _radius;
    if((_pos.x + diameter) >= WORK_PANEL) {
        _vel.x *= -1;
        _pos.x += _vel.x;
    }
    if(_pos.x <= 0) {
        _vel.x *= -1;
        _pos.x += _vel.x;
    }
    if((_pos.y + diameter) >= SCREEN_HEIGHT) {
        _vel.y *= -1;
        _pos.y += _vel.y;
    }
    if(_pos.y <= 0) {
        _vel.y *= -1;
        _pos.y += _vel.y;
    }
}

void Particle::Draw(sf::RenderWindow& window) {
    sf::CircleShape _shape = sf::CircleShape(_radius);
    _shape.setPosition(_pos);
    _shape.setFillColor(_fill_color);

    window.draw(_shape);
}