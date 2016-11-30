//
// Created by Neil Connatty on 2016-11-30.
//

#include "states/pause_state.h"

pause_state::pause_state(state_stack &stack, context cntxt) :
        state(stack, cntxt),
        m_paused_text(),
        m_instruction_text()
{
}

void pause_state::draw ()
{
    sf::RenderWindow& window = *get_context().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));

    window.draw(backgroundShape);
    window.draw(m_paused_text);
    window.draw(m_instruction_text);
}

bool pause_state::update (sf::Time dt)
{
    return false;
}

bool pause_state::handle_event (const sf::Event &event)
{
    if (event.key.code == sf::Keyboard::Escape) {
        request_stack_pop();
    } else if (event.key.code == sf::Keyboard::BackSpace) {
        request_state_clear();
        request_stack_push(states::MENU);
    }

    return false;
}