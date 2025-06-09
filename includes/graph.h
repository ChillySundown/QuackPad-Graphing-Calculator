#ifndef DARWICH_GRAPH_H
#define DARWICH_GRAPH_H

#include "particle.h"
#include "plot.h"
#include "graph_info.h"
#include "../includes/vector/vector.h"
#include <SFML/Graphics.hpp>

class Graph {
    public:
        Graph();
        Graph(Plot p);
        Graph(GraphInfo* info);

        void set_info(GraphInfo* newInfo); //Do we need this?
        void update(GraphInfo* g);
        void Draw(sf::RenderWindow& w);

    private:
        Plot _plot;

        sf::Vertex dots[300];

        GraphInfo* info;

        sf::RectangleShape x_axis;
        sf::RectangleShape y_axis;

        sf::CircleShape circle1;
        sf::CircleShape circle2;
        sf::CircleShape circle3;

        sf::RectangleShape positive30;
        sf::RectangleShape positive60;
        sf::RectangleShape negative30;
        sf::RectangleShape negative60;
        
};
#endif