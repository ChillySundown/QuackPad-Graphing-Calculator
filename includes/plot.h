#ifndef DARWICH_PLOT_H
#define DARWICH_PLOT_H

#include "rpn/rpn.h"
#include "shunting_yard/shunting_yard.h"
#include <cmath>
#include "../includes/vector/vector.h"
#include "graph_info.h"
#include <SFML/Graphics.hpp>

class Plot {
    public:
        Plot();

        Plot(int xmin, int xmax, Queue<Token*>& t);

        Plot(GraphInfo* info);

        sf::Vector2f translate(sf::Vector2f& _point);

        void set_info(GraphInfo* info);

        Vector<sf::Vector2f> operator()();

        Vector<sf::Vector2f>& get_points();

    private:
        Vector<sf::Vector2f> _points;
        // Queue<Token*> postfix;
        GraphInfo* _info; //REMINDER YOU NEED A GraphInfo at EVERY LEVEL!!! Use It In Constructor!!!

};
#endif