//
// Created by Neil Connatty on 2016-11-15.
//

#ifndef SFMLENGINE_SPRITE_NODE_H
#define SFMLENGINE_SPRITE_NODE_H


#include "scene_node.h"
#include <SFML/Graphics/Sprite.hpp>

class sprite_node : public scene_node
{
public:
    explicit sprite_node (const sf::Texture& texture);
    sprite_node (const sf::Texture& texture, const sf::IntRect& rect);

private:
    virtual void draw_current (sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite _sprite;
};


#endif //SFMLENGINE_SPRITE_NODE_H
