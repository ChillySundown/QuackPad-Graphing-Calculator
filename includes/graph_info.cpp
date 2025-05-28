#include "graph_info.h"
#include "constants.h"
#include "token/function.h"
GraphInfo::GraphInfo() {
    _max_x_screen = SCREEN_WIDTH;
    _max_y_screen = SCREEN_HEIGHT;
    _x_min = -5;
    _x_max = 5;
    _y_min = -5;
    _y_max = 5;
    _q.push(new Function("x"));
    _points = 10;
    // _window_dimensions = sf::Vector2f(600.f, 600.f);
    // _origin = sf::Vector2f(300.f, 300.f);
    // _domain = sf::Vector2f(-5.f, 5.f);
    // _equation = "x";

}

GraphInfo::GraphInfo(float x_screen, float y_screen, float x_min, float x_max, float y_min, float y_max, Queue<Token*> q) {
    _max_x_screen = x_screen;
    _max_y_screen = y_screen;
    _x_min = x_min;
    _x_max = x_max;
    _y_min = y_min;
    _y_max = y_max;
    _q = q;
}

float GraphInfo::get_x_screen() {
    return _max_x_screen;
}
float GraphInfo::get_y_screen() {
    return _max_y_screen;
}
float GraphInfo::get_x_min() {
    return _x_min;
}
float GraphInfo::get_x_max() {
    return _x_max;
}
float GraphInfo::get_y_min() {
    return _y_min;
}
float GraphInfo::get_y_max() {
    return _y_max;
}

int GraphInfo::getNumPoints() {
    return _points;
}

void GraphInfo::set_x(float x_min, float x_max) {
    _x_min = x_min;
    _x_max = x_max;
}
void GraphInfo::set_y(float y_min, float y_max) {
    _y_min = y_min;
    _y_max = y_max;
}


// Queue<Token*> GraphInfo::tokenizer(string expression) {
//     while(!expression.empty()) {
//     }
//     return Queue<Token*>();
// }

Queue<Token*>& GraphInfo::get_expression() {
    return _q;
}