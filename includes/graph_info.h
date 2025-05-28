#ifndef DARWICH_GRAPH_INFO_H
#define DARWICH_GRAPH_INFO_H

#include "queue/MyQueue.h"
#include "token/token.h"
#include <cstring>
#include <SFML/Graphics.hpp>

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
        void setNumPoints(int num);
        void setEquation(string eq);
        void setEquation(Queue<Token*>& t);

        int getNumPoints();

        Queue<Token*>& get_expression();
        
    private:
        // string _equation;
        // sf::Vector2f _window_dimensions;
        // sf::Vector2f _origin;
        // sf::Vector2f _scale;
        // sf::Vector2f _domain;
        int _points;

        float _max_x_screen;
        float _max_y_screen;
        float _x_min;
        float _x_max;
        float _y_min;
        float _y_max;
        Queue<Token*> _q;

        Queue<Token*> tokenizer(string _equation);
};
#endif