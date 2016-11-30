//
// Created by Neil Connatty on 2016-11-03.
//

#include "scene/aircraft.h"

using namespace textures;

textures::ID to_texture_id (aircraft::type m_type)
{
    switch (m_type) {
        case aircraft::EAGLE :
            return textures::EAGLE;

        case aircraft::RAPTOR :
            return textures::RAPTOR;
    }
}


aircraft::aircraft (aircraft::type m_type, const texture_holder &textures) : m_type(m_type), m_sprite(textures.get(to_texture_id(m_type)))
{
    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void aircraft::draw_current(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

unsigned int aircraft::get_category () const
{
    switch (m_type)
    {
        case aircraft::EAGLE:
            return category::PLAYER_AIRCRAFT;
        default:
            return category::ENEMY_AIRCRAFT;
    }
}

