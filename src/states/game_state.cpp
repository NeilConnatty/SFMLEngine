//
// Created by Neil Connatty on 2016-11-28.
//

#include "states/game_state.h"

game_state::game_state (state_stack &stack, context cntxt) :
        state(stack, cntxt),
        m_world(*cntxt.window),
        m_player(*cntxt.the_player)
{
}

void game_state::draw ()
{
    m_world.draw();
}

bool game_state::handle_event (const sf::Event &event)
{
    command_queue& commands = m_world.get_command_queue();
    m_player.handle_event(event, commands);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        request_stack_push(states::PAUSE);

    return true;
}

bool game_state::update (sf::Time dt)
{
    m_world.update(dt);

    command_queue& commands = m_world.get_command_queue();
    m_player.handle_realtime_input(commands);

    return true;
}

