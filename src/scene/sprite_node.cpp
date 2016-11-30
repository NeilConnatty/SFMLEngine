//
// Created by Neil Connatty on 2016-11-15.
//

#include "scene/sprite_node.h"

sprite_node::sprite_node (const sf::Texture &texture) :
        m_sprite(texture)
{
}

sprite_node::sprite_node (const sf::Texture &texture, const sf::IntRect& rect) :
        m_sprite(texture, rect)
{
}

void sprite_node::draw_current (sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}