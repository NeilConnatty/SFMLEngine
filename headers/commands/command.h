//
// Created by Neil Connatty on 2016-11-25.
//

#ifndef SFMLENGINE_COMMAND_H
#define SFMLENGINE_COMMAND_H

#include <SFML/Time.hpp>
#include "scene/category.h"

#include <functional>
#include <cassert>

class scene_node;

struct command
{
    command();

    std::function<void(scene_node&, sf::Time)>  action;
    unsigned int                                category;
};

template <typename game_object, typename function>
std::function<void(scene_node& node, sf::Time dt)> derived_action(function fn)
{
    return [=] (scene_node& node, sf::Time dt)
    {
        assert(dynamic_cast<game_object*>(&node) != nullptr);
        fn(static_cast<game_object&>(node), dt);
    };
}

#endif //SFMLENGINE_COMMAND_H
