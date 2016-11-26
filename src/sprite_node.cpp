//
// Created by Neil Connatty on 2016-11-15.
//

#include "sprite_node.h"

sprite_node::sprite_node (const sf::Texture &texture) :
        _sprite(texture)
{
}

sprite_node::sprite_node (const sf::Texture &texture, const sf::IntRect& rect) :
        _sprite(texture, rect)
{
}

void sprite_node::draw_current (sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}