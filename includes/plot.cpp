#include "plot.h"

Plot::Plot() { //Currently using for all testing

}

Plot::Plot(int xmin, int xmax, Queue<Token*>& t) {
    ShuntingYard s(t);
    Queue<Token*> post = s.postfix();
    RPN r;
    for(int i = xmin; i <= xmax; i++) {
        r.set_input(post);
        _points.push_back(sf::Vector2f(i, r(i)));
    }
    //translate();
}

Plot::Plot(GraphInfo* info) {
    
}

vector<sf::Vector2f> Plot::operator()() {
    ShuntingYard yard(_info->get_expression());
    Queue<Token*> post = yard.postfix();
    RPN r;
    float x_max = _info->get_x_max();
    float x_min = _info->get_x_min();
    int numPoints = _info->getNumPoints();
    float inc = (x_max - x_min) / numPoints;
    for(float i = x_min; i <= x_max; i += inc) {
        r.set_input(post);
        sf::Vector2f pre_translate = sf::Vector2f(i, r(i));
        _points.push_back(translate(pre_translate));
    }
    //translate();
    return _points;
}

void Plot::set_info(GraphInfo* info) { //Takes the new graph information and plots the points in the emptied vector
    _info = info;
    _points.clear();
    // ShuntingYard s(info->get_expression());
    // _points.clear(); //Clears vector before pushing new coords
    // Queue<Token*> post = s.postfix();
    // RPN y;
    // float inc = (info->get_x_max() - info->get_x_min()) / info->getNumPoints();
    // for(float x = info->get_x_min(); x <= info->get_x_max(); x += inc) {
    //     y.set_input(post);
    //     _points.push_back(sf::Vector2f(x, y(x)));
    // }
    // translate();
}

sf::Vector2f Plot::translate(sf::Vector2f& _point) {
    float x_min = _info->get_x_min();
    float x_max = _info->get_x_max();
    int numPoints = _info->getNumPoints();

    float new_x, new_y;

    new_y = 300 - _point.y;
    if(x_min < 0)
        new_x = numPoints * (_point.x - x_min);
    else {
         new_x = _point.x + (600 - x_max);
    }
    return sf::Vector2f(new_x, new_y);
} 

vector<sf::Vector2f>& Plot::get_points() {
    return _points;
}

