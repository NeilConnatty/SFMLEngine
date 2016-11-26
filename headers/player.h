//
// Created by Neil Connatty on 2016-11-25.
//

#ifndef SFMLENGINE_PLAYER_H
#define SFMLENGINE_PLAYER_H

#include "command_queue.h"
#include "command.h"

#define PLAYER_SPEED 200.f

class player
{
public:
    player ();

    enum action
    {
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_UP,
        MOVE_DOWN,
        PRINT_POSITION
    };

    void assign_key (action act, sf::Keyboard::Key key);
    sf::Keyboard::Key get_assigned_key (action act) const;

    void handle_event (const sf::Event& event, command_queue& commands);
    void handle_realtime_input (command_queue& commands);

private:
    static bool is_realtime_action (action act);
    void initialize_actions ();

private:
    std::map<sf::Keyboard::Key, action> m_keyBinding;
    std::map<action, command> m_actionBinding;
};


#endif //SFMLENGINE_PLAYER_H
