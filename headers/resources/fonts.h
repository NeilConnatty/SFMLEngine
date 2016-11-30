//
// Created by Neil Connatty on 2016-11-27.
//

#ifndef SFMLENGINE_FONTS_H
#define SFMLENGINE_FONTS_H

#include <SFML/Graphics.hpp>

#include "resource_holder.h"

namespace sf {
    class Font;
}

namespace fonts
{
    enum ID {
        DEFAULT
    };
}

template <typename resource, typename identifier>
class resource_holder;

typedef resource_holder<sf::Font, fonts::ID> font_holder;

#endif //SFMLENGINE_FONTS_H
