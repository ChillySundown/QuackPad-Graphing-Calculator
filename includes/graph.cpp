#include "graph.h"
#include "plot.h"

Graph::Graph() {
    _plot = Plot();
}

Graph::Graph(Plot p) {
    _plot = p;
}

void Graph::Draw(sf::RenderWindow& w) {
    Particle a(sf::Vector2f(600.f, 600.f)); //Origin
    Particle b(sf::Vector2f(1200.f, 600.f));
    Particle c(sf::Vector2f(300.f, 0.f));
    Particle d(sf::Vector2f(0.f, 300.f));
    Particle e(sf::Vector2f(300.f, 600.f));

    a.Draw(w);
    b.Draw(w);
    c.Draw(w);
    d.Draw(w);
    e.Draw(w);
    vector<sf::Vector2f> v = _plot.get_points();
    for(int i = 0; i < v.size(); i++) {
        sf::CircleShape _point;
        _point.setPosition(v[i]);
        w.draw(_point);
    }
}

void Graph::set_info(GraphInfo* info) {
    _plot.set_info(info);
}