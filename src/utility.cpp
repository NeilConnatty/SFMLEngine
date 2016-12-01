//
// Created by Neil Connatty on 2016-11-30.
//

#include <SFML/Graphics.hpp>

#include "utility.h"

void utility::centre_origin (sf::Sprite& sprite)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void utility::centre_origin (sf::Text &text)
{
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}