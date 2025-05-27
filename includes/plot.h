#ifndef DARWICH_PLOT_H
#define DARWICH_PLOT_H

#include "rpn/rpn.h"
#include "shunting_yard/shunting_yard.h"
#include <cmath>
#include <vector>
#include "graph_info.h"
#include <SFML/Graphics.hpp>

class Plot {
    public:
        Plot();

        Plot(int xmin, int xmax, Queue<Token*>& t);

        Plot(GraphInfo* info);

        void translate();

        void set_info(GraphInfo newInfo);

        vector<sf::Vector2f> operator()();

        vector<sf::Vector2f>& get_points();

    private:
        vector<sf::Vector2f> _points;
        // Queue<Token*> postfix;
        // GraphInfo* info;

};
#endif