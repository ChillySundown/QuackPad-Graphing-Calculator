#include "graph.h"
#include "plot.h"

using namespace std;

Graph::Graph() {
    _plot = Plot();
    x_axis = sf::RectangleShape(sf::Vector2f(600.f, 3.f));
    y_axis = sf::RectangleShape(sf::Vector2f(3.f, 600.f));
    x_axis.setPosition(sf::Vector2f(0.f, 300.f));
    y_axis.setPosition(sf::Vector2f(300.f, 0.f));
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
    vector<sf::Vector2f> v = _plot();
    for(int i = 0; i < v.size(); i++) {
        sf::CircleShape _point(3.f);
        _point.setFillColor(sf::Color(0,200,0));
        _point.setPosition(v[i]);
        w.draw(_point);
    }
}

void Graph::set_info(GraphInfo* g) {
    cout << "Busy doing nothing :/";
}

void Graph::update(GraphInfo* g) {
    _plot.set_info(g);
}

