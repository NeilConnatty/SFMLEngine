//
// Created by Neil Connatty on 2016-11-03.
//

#ifndef SFMLENGINE_AIRCRAFT_H
#define SFMLENGINE_AIRCRAFT_H

#include "entity.h"
#include <SFML/Graphics.hpp>
#include "textures.h"

class aircraft : public entity
{
public:
    enum type {
        EAGLE,
        RAPTOR,
    };

public:
    explicit aircraft (aircraft::type m_type, const texture_holder &textures);
    virtual void draw_current (sf::RenderTarget &target, sf::RenderStates states) const;

private:
    type _type;
    sf::Sprite _sprite;
};


#endif //SFMLENGINE_AIRCRAFT_H
