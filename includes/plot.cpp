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
    translate();
}

Plot::Plot(GraphInfo* info) {
    
}

vector<sf::Vector2f> Plot::operator()() {
    Queue<Token*> s;
    s.push(new Function("x"));
    ShuntingYard yard(s);
    Queue<Token*> post = yard.postfix();
    RPN r;
    float inc = (5.f - -5.f) / 11;
    for(float i = -5.f; i <= 5.f; i += inc) {
        r.set_input(post);
        _points.push_back(sf::Vector2f(i, r(i)));
    }
    translate();
    return _points;
}

void Plot::set_info(GraphInfo* info) { //Takes the new graph information and plots the points in the emptied vector
    ShuntingYard s(info->get_expression());
    _points.clear(); //Clears vector before pushing new coords
    Queue<Token*> post = s.postfix();
    RPN y;
    float inc = (info->get_x_max() - info->get_x_min()) / info->getNumPoints();
    for(float x = info->get_x_min(); x <= info->get_x_max(); x += inc) {
        y.set_input(post);
        _points.push_back(sf::Vector2f(x, y(x)));
    }
    translate();
}

void Plot::translate() {
    for(int i = 0; i < _points.size(); i++) {
        _points[i] = sf::Vector2f(10* _points[i].x + 300, 300 - (10 * _points[i].y));
    }
} 

vector<sf::Vector2f>& Plot::get_points() {
    return _points;
}

