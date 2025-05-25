#include "graph.h"
#include "plot.h"

Graph::Graph() {
    _plot = Plot();
    x_axis = sf::RectangleShape(sf::Vector2f(800.f, 3.f));
    y_axis = sf::RectangleShape(sf::Vector2f(3.f, 800.f));
    x_axis.setPosition(sf::Vector2f(0.f, 400.f));
    y_axis.setPosition(sf::Vector2f(400.f, 0.f));
    x_axis.setFillColor(sf::Color::White);
    y_axis.setFillColor(sf::Color::White);
}

Graph::Graph(Plot p) {
    _plot = p;
}

Graph::Graph(GraphInfo* info) {
    _plot = Plot(info);
}

void Graph::Draw(sf::RenderWindow& w) {
    w.draw(x_axis);
    w.draw(y_axis);
    vector<sf::Vector2f> v = _plot.get_points();
    for(int i = 0; i < v.size(); i++) {
        sf::CircleShape _point(4.f);
        _point.setFillColor(sf::Color(0,200,0));
        _point.setPosition(v[i]);
        w.draw(_point);
    }
}

void Graph::set_info(GraphInfo* info) {
    _plot.set_info(info);
}