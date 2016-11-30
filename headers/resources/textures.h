//
// Created by Neil Connatty on 2016-11-10.
//

#ifndef SFMLENGINE_TEXTURES_H
#define SFMLENGINE_TEXTURES_H

#include <SFML/Graphics.hpp>
#include "resource_holder.h"

namespace sf
{
    class Texture;
}

namespace textures
{
    enum ID
    {
        EAGLE,
        RAPTOR,
        DESERT,
        TITLE_SCREEN
    };
}

template <typename resource, typename identifier>
class resource_holder;

typedef resource_holder<sf::Texture, textures::ID> texture_holder;

#endif //SFMLENGINE_TEXTURES_H
