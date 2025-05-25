#include "plot.h"

Plot::Plot() { //Currently using for all testing
    Queue<Token*> s;
    s.push(new Integer(1));
    s.push(new Operator("*"));
    s.push(new Function("x"));
    s.push(new Operator("^"));
    s.push(new Integer(2));
    ShuntingYard yard(s);
    Queue<Token*> post = yard.postfix();
    RPN r;
    for(float i = -10.f; i <= 10.f; i = i + 0.1) {
        r.set_input(post);
        _points.push_back(sf::Vector2f(i, r(i)));
    }
    translate();
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

void Plot::set_info(GraphInfo* info) { //Takes the new graph information and plots the points in the emptied vector
    ShuntingYard s(info->get_expression());
    _points.clear(); //Clears vector before pushing new coords
    Queue<Token*> post = s.postfix();
    RPN y;
    for(float x = info->get_x_min(); x <= info->get_x_max(); x += 0.1) {
        y.set_input(post);
        _points.push_back(sf::Vector2f(x, y(x)));
    }
    translate();
}

void Plot::translate() {
    for(int i = 0; i < _points.size(); i++) {
        _points[i] = sf::Vector2f(10 * _points[i].x + 400, 400 - (4 * _points[i].y));
    }
} 

vector<sf::Vector2f>& Plot::get_points() {
    return _points;
}

