#ifndef DARWICH_GRAPH_H
#define DARWICH_GRAPH_H

#include "particle.h"
#include "plot.h"
#include "graph_info.h"
#include <SFML/Graphics.hpp>

class Graph {
    public:
        Graph();
        Graph(Plot p);
        Graph(GraphInfo* info);

        void set_info(GraphInfo* newInfo); //Do we need this?
        void update(GraphInfo g);
        void Draw(sf::RenderWindow& w);

    private:
        Plot _plot;
        sf::RectangleShape x_axis;
        sf::RectangleShape y_axis;
};

#endif