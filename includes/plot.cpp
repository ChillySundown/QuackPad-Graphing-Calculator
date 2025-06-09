#include "plot.h"
#include "constants.h"


Plot::Plot() { 
//Don't really use this
}


Plot::Plot(GraphInfo* info) {
//Or that for that matter
}

Vector<sf::Vector2f> Plot::operator()() { //The hero of this program!
    if(!_info->get_expression().empty()) { //If given expression is not empty, operate
        ShuntingYard yard(_info->get_expression()); //Runs ShuntingYard
        Queue<Token*> post = yard.postfix(); //Sets postfix from ShuntingYard function
        RPN r;
        float x_max = _info->get_x_max(); //Initializes x-min/max/numPoints
        float x_min = _info->get_x_min();
        int numPoints = _info->getNumPoints();
        float inc = (x_max - x_min) / (numPoints-1); //Gets us an interval
        for(float i = x_min; i <= x_max; i += inc) { //Loops from min to max in increment-long steps
            //Resets the RPN object to hold the untouched postfix;
            r.set_input(post);
            try {
                sf::Vector2f pre_translate = sf::Vector2f(i, r(i)); //Creates a sf::Vector2f that holds the x-pos and the rpn product
                _points += (translate(pre_translate)); //Runs translate on the vector before push_back
            } catch(exception e) {
            //Just skip over bro;
            }
        }   
    }
    return _points;
}

void Plot::set_info(GraphInfo* info) { //Takes the new graph information and plots the points in the emptied vector
    _info = info;
    for(int i = _points.size(); i > 0; i--) {
        sf::Vector2f deleter = _points.pop_back();
    }
}

sf::Vector2f Plot::translate(sf::Vector2f& _point) {
    float x_min = _info->get_x_min(); //Gets min/max information
    float x_max = _info->get_x_max();
    int numPoints = _info->getNumPoints(); //Gets numPoints

    float new_x, new_y;

    float x_interval = WORK_PANEL / (_info->get_x_max() - _info->get_x_min()); //Calculates transformation constant to multiply points by
    float y_interval = SCREEN_HEIGHT / (_info->get_y_max() - _info->get_y_min());

    new_y = (SCREEN_HEIGHT / 2) - (y_interval * _point.y) - 1.f; //Subtracts the transformation constant of y from y = 0
    new_x =  (x_interval) * (_point.x - x_min) - 1.f; //Multiplies the transformation constant by the differenct between x-min and our point's x
    //Note that we subtract 1.f from both new_x and new_y because we need to account for dot size

    return sf::Vector2f(new_x, new_y);
} 

Vector<sf::Vector2f>& Plot::get_points() {
    return _points;
}

