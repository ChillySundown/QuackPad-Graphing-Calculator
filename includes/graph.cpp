#include "graph.h"
#include "plot.h"

using namespace std;

Graph::Graph() {
    _plot = Plot();
    x_axis = sf::RectangleShape(sf::Vector2f(WORK_PANEL, 1.f));
    y_axis = sf::RectangleShape(sf::Vector2f(1.f, SCREEN_HEIGHT));
    x_axis.setPosition(sf::Vector2f(0.f, SCREEN_HEIGHT / 2));
    y_axis.setPosition(sf::Vector2f(WORK_PANEL /2, 0.f));
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

    sf::Vector2f origin = sf::Vector2f(0, 0);
    sf::Vector2f orgin_trans = sf::Vector2f(_plot.translate(origin).x, 0);
    y_axis.setPosition(orgin_trans);

    w.draw(y_axis);

    vector<sf::Vector2f> v = _plot();
    for(int i = 0; i < v.size(); i++) {
        sf::CircleShape _point(1.f);
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

