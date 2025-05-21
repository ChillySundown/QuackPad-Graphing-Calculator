#include "graph.h"
#include "plot.h"

Graph::Graph() {
    _plot = Plot();
}

Graph::Graph(Plot p) {
    _plot = p;
}

void Graph::Draw(sf::RenderWindow& w) {
    vector<sf::Vector2f> v = _plot.get_points();
    for(int i = 0; i < v.size(); i++) {
        Particle p(v[i]);
        p.Draw(w);
    }
}