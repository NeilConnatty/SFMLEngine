//
// Created by Neil Connatty on 2016-11-30.
//

#ifndef SFMLENGINE_UTILITY_H
#define SFMLENGINE_UTILITY_H

#include <sstream>
#include <SFML/Window/Keyboard.hpp>

namespace sf
{
    class Sprite;
    class Text;
}

namespace utility
{
    void centre_origin(sf::Sprite &sprite);
    void centre_origin(sf::Text &text);

    std::string to_string(sf::Keyboard::Key key);
}

#endif //SFMLENGINE_UTILITY_H
