//
// Created by Neil Connatty on 2016-11-27.
//

#include "states/state.h"
#include "states/state_stack.h"

state::context::context(sf::RenderWindow &window,
                        texture_holder &textures,
                        font_holder &fonts,
                        player &the_player) :
        window(&window),
        textures(&textures),
        fonts(&fonts),
        the_player(&the_player)
{
}

state::state (state_stack &stack, context cntxt) :
        m_context(cntxt),
        m_stack(&stack)
{
}

state::~state ()
{
}

void state::request_stack_pop()
{
    m_stack->pop_state();
}

void state::request_stack_push(states::ID stateID)
{
    m_stack->push_state(stateID);
}

void state::request_state_clear()
{
    m_stack->clear_states();
}

state::context state::get_context() const
{
    return m_context;
}