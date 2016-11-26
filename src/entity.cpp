//
// Created by Neil Connatty on 2016-11-03.
//

#include "entity.h"

void entity::set_velocity (sf::Vector2f velocity)
{
    m_velocity = velocity;
}

void entity::set_velocity (float vx, float vy)
{
    m_velocity.x = vx;
    m_velocity.y = vy;
}

sf::Vector2f entity::get_velocity () const
{
    return m_velocity;
}

void entity::update_current (sf::Time dt)
{
    move(m_velocity * dt.asSeconds());
}

void entity::accelerate (sf::Vector2f velocity)
{
    set_velocity(this->get_velocity() + velocity);
}

void entity::accelerate (float vx, float vy)
{
    set_velocity(this->get_velocity() + sf::Vector2f(vx, vy));
}