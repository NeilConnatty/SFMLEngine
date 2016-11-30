//
// Created by Neil Connatty on 2016-11-03.
//

#ifndef SFMLENGINE_ENTITY_H
#define SFMLENGINE_ENTITY_H

#include <SFML/System.hpp>
#include "scene_node.h"

class entity : public scene_node
{
public:
    void            set_velocity (sf::Vector2f velocity);
    void            set_velocity (float vx, float vy);
    void            accelerate (sf::Vector2f velocity);
    void            accelerate (float vx, float vy);

    sf::Vector2f    get_velocity () const;

private:
    virtual void    update_current (sf::Time dt);

private:
    sf::Vector2f    m_velocity;
};


#endif //SFMLENGINE_ENTITY_H
