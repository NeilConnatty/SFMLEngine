//
// Created by Neil Connatty on 2016-11-10.
//

#ifndef SFMLENGINE_TEXTURES_H
#define SFMLENGINE_TEXTURES_H

#include <SFML/Graphics.hpp>
#include "resource_holder.h"

namespace textures
{
    enum ID
    {
        EAGLE,
        RAPTOR,
        DESERT,
    };

    typedef resource_holder<sf::Texture, textures::ID> texture_holder;
}

#endif //SFMLENGINE_TEXTURES_H
