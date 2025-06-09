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

    circle1 = sf::CircleShape(WORK_PANEL / 6);
    circle2 = sf::CircleShape (WORK_PANEL / 3);
    circle3 = sf::CircleShape(WORK_PANEL / 2);

    circle1.setPointCount(100);
    circle2.setPointCount(150);
    circle3.setPointCount(200);

    sf::Vector2f posCircle1 = sf::Vector2f((WORK_PANEL / 2.f) - (WORK_PANEL / 6.f), (SCREEN_HEIGHT / 2.f) - (WORK_PANEL / 6.f));//(3 * WORK_PANEL) / 4.f,  (5* WORK_PANEL) / 4.f);
    sf::Vector2f posCircle2 = sf::Vector2f((WORK_PANEL / 2.f) - (WORK_PANEL / 3.f), (SCREEN_HEIGHT / 2.f) - (WORK_PANEL / 3.f));
    sf::Vector2f posCircle3 = sf::Vector2f((WORK_PANEL / 2.f) - (WORK_PANEL / 2.f), (SCREEN_HEIGHT / 2.f) - (WORK_PANEL / 2.f));

    circle1.setPosition(posCircle1);
    circle2.setPosition(posCircle2);
    circle3.setPosition(posCircle3);

    circle1.setFillColor(sf::Color::Transparent);
    circle2.setFillColor(sf::Color::Transparent);
    circle3.setFillColor(sf::Color::Transparent);

    circle1.setOutlineThickness(4.f);
    circle1.setOutlineColor(sf::Color::White);

    circle2.setOutlineColor(sf::Color::White);
    circle2.setOutlineThickness(4.f);

    circle3.setOutlineColor(sf::Color::White);
    circle3.setOutlineThickness(4.f);

    positive30 = sf::RectangleShape(sf::Vector2f(1500, 1.f));
    positive30.setFillColor(sf::Color::White);

    negative30 = sf::RectangleShape(sf::Vector2f(1500, 1.f));
    negative30.setFillColor(sf::Color::White);

    positive60 = sf::RectangleShape(sf::Vector2f(1500, 1.f));
    positive60.setFillColor(sf::Color::White);

    negative60 = sf::RectangleShape(sf::Vector2f(1500, 1.f));
    negative60.setFillColor(sf::Color::White);

    positive30.setPosition(sf::Vector2f(0, (3.25 * SCREEN_HEIGHT) / 4.f));
    positive30.rotate(sf::degrees(-24));

    positive60.setPosition(sf::Vector2f(WORK_PANEL / 4.f, SCREEN_HEIGHT));
    positive60.rotate(sf::degrees(-55));

    negative60.setPosition(sf::Vector2f((3 * WORK_PANEL)/ 4.f, SCREEN_HEIGHT));
    negative60.rotate(sf::degrees(-125));

    negative30.setPosition(sf::Vector2f(WORK_PANEL, (3.25 * SCREEN_HEIGHT) / 4.f));
    negative30.rotate(sf::degrees(-156));

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

    sf::Vector2f circle1_origin = sf::Vector2f(_plot.translate(origin).x - circle1.getRadius(), circle1.getPosition().y);
    circle1.setPosition(circle1_origin);
    
    sf::Vector2f circle2_origin = sf::Vector2f(_plot.translate(origin).x - circle2.getRadius(), circle2.getPosition().y);
    circle2.setPosition(circle2_origin);

    sf::Vector2f circle3_origin = sf::Vector2f(_plot.translate(origin).x - circle3.getRadius(), circle3.getPosition().y);
    circle3.setPosition(circle3_origin);

    positive30.setPosition(sf::Vector2f(_plot.translate(origin).x - WORK_PANEL / 2, positive30.getPosition().y));
    positive60.setPosition(sf::Vector2f(_plot.translate(origin).x - WORK_PANEL / 4, positive60.getPosition().y));
    negative60.setPosition(sf::Vector2f(_plot.translate(origin).x + WORK_PANEL / 4, negative60.getPosition().y));
    negative30.setPosition(sf::Vector2f(_plot.translate(origin).x + WORK_PANEL / 2, negative30.getPosition().y));

    w.draw(y_axis);

    if(info->isPolar()) {
        w.draw(circle1);
        w.draw(circle2);
        w.draw(circle3);
        w.draw(positive30);
        w.draw(positive60);
        w.draw(negative60);
        w.draw(negative30);
    }

    Vector<sf::Vector2f> v = _plot();
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
    info = g;
    _plot.set_info(g);
}

