//
// Created by Neil Connatty on 2016-11-03.
//

#include "entity.h"

void entity::set_velocity (sf::Vector2f velocity)
{
    _velocity = velocity;
}

void entity::set_velocity (float vx, float vy)
{
    _velocity.x = vx;
    _velocity.y = vy;
}

sf::Vector2f entity::get_velocity () const
{
    return _velocity;
}