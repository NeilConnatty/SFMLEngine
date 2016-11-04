//
// Created by Neil Connatty on 2016-11-03.
//

#ifndef SFMLENGINE_ENTITY_H
#define SFMLENGINE_ENTITY_H

#include <SFML/System.hpp>

class entity
{
public:
    void set_velocity (sf::Vector2f velocity);
    void set_velocity (float vx, float vy);
    sf::Vector2f get_velocity () const;

private:
    sf::Vector2f _velocity;
};


#endif //SFMLENGINE_ENTITY_H
