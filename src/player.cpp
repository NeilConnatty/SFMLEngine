//
// Created by Neil Connatty on 2016-11-25.
//

#include <aircraft.h>
#include <iostream>
#include "player.h"

struct aircraft_mover
{
    aircraft_mover (float vx, float vy) : velocity(vx, vy)
    {
    }

    void operator () (aircraft& craft, sf::Time dt)
    {
        craft.accelerate(velocity);
    }

    sf::Vector2f velocity;
};

player::player ()
{
    m_keyBinding[sf::Keyboard::Left] = MOVE_LEFT;
    m_keyBinding[sf::Keyboard::Right] = MOVE_RIGHT;
    m_keyBinding[sf::Keyboard::P] = PRINT_POSITION;

    initialize_actions();

    for (auto pair : m_actionBinding) {
        pair.second.category = category::PLAYER_AIRCRAFT;
    }
}

void player::handle_event (const sf::Event &event, command_queue &commands)
{
    if (event.type == sf::Event::KeyPressed)
    {
        auto found = m_keyBinding.find(event.key.code);
        if (found != m_keyBinding.end() && !is_realtime_action(found->second))
            commands.push(m_actionBinding[found->second]);
    }
}

void player::handle_realtime_input (command_queue &commands)
{
    for (auto pair : m_keyBinding)
    {
        if (sf::Keyboard::isKeyPressed(pair.first) && is_realtime_action(pair.second)) {
            commands.push(m_actionBinding[pair.second]);
        }
    }
}

void player::assign_key (action act, sf::Keyboard::Key key)
{
    // remove all keys that already map to action
    for (auto itr = m_keyBinding.begin(); itr != m_keyBinding.end(); )
    {
        if (itr->second == act) {
            m_keyBinding.erase(itr++);
        } else {
            ++itr;
        }
        // insert new binding
        m_keyBinding[key] = act;
    }
}

sf::Keyboard::Key player::get_assigned_key (action act) const
{
    for (auto pair : m_keyBinding)
    {
        if (pair.second == act) {
            return pair.first;
        }
    }

    return sf::Keyboard::Unknown;
}

void player::initialize_actions ()
{
    const float playerSpeed = PLAYER_SPEED;

    m_actionBinding[PRINT_POSITION].action = [](scene_node& node, sf::Time dt)
    {
        std::cout << node.getPosition().x << "," << node.getPosition().y << std::endl;
    };

    m_actionBinding[MOVE_LEFT].action = derived_action<aircraft>(aircraft_mover(-playerSpeed, 0.f));
    m_actionBinding[MOVE_RIGHT].action = derived_action<aircraft>(aircraft_mover(playerSpeed, 0.f));
    m_actionBinding[MOVE_UP].action = derived_action<aircraft>(aircraft_mover(0.f, -playerSpeed));
    m_actionBinding[MOVE_DOWN].action = derived_action<aircraft>(aircraft_mover(0.f, playerSpeed));
}

static bool player::is_realtime_action (action act)
{
    switch (act)
    {
        case MOVE_DOWN:
        case MOVE_RIGHT:
        case MOVE_UP:
        case MOVE_LEFT:
            return true;

        default:
            return false;
    }
}