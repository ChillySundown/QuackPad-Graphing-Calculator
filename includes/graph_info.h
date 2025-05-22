#ifndef DARWICH_GRAPH_INFO
#define DARWICH_GRAPH_INFO

#include "graph.h"
#include "plot.h"
#include "../includes/token/token.h"

class GraphInfo {
    public:
        GraphInfo();

        GraphInfo(float x_screen, float y_screen, float x_min, float x_max, float y_min, float y_max, Queue<Token*> q);

        float get_x_screen();
        float get_y_screen();
        float get_x_min();
        float get_x_max();
        float get_y_min();
        float get_y_max();

        void set_x(float x_min, float x_max);
        void set_y(float y_min, float y_max);

        Queue<Token*>& get_expression();
        
    private:
        float _max_x_screen;
        float _max_y_screen;
        float _x_min;
        float _x_max;
        float _y_min;
        float _y_max;
        Queue<Token*> _q;
};
#endif