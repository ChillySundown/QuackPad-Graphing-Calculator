#ifndef DARWICH_PLOT_H
#define DARWICH_PLOT_H

#include "rpn/rpn.h"
#include "shunting_yard/shunting_yard.h"
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>

class Plot {
    public:
        Plot();

        Plot(int xmin, int xmax, Queue<Token*>& t);

        void translate();

        vector<sf::Vector2f>& get_points();

    private:
        vector<sf::Vector2f> _points;
};
#endif