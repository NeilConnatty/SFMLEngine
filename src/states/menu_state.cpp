//
// Created by Neil Connatty on 2016-11-30.
//

#include "states/menu_state.h"

menu_state::menu_state (state_stack &stack, state::context cntxt) :
        state(stack, cntxt),
        m_options(),
        m_optionIndex(0)
{
    sf::Text playOption;
    playOption.setFont(cntxt.fonts->get(fonts::DEFAULT));
    playOption.setString("Play");
    center_origin(playOption);
    playOption.setPosition(cntxt.window->getView().getSize() / 2.f);
    m_options.push_back(playOption);
}

void menu_state::update_option_text ()
{
    if (m_options.empty()) return;

    for (sf::Text& text : m_options) {
        text.setFillColor(sf::Color::White);
    }

    m_options[m_optionIndex].setFillColor(sf::Color::Red);
}

void menu_state::draw ()
{
}

bool menu_state::update (sf::Time dt)
{
}

bool menu_state::handle_event (const sf::Event &event)
{
    if (event.key.code == sf::Keyboard::Up)
    {
        if (m_optionIndex > 0) m_optionIndex--;
        else m_optionIndex = m_options.size() - 1;

        update_option_text();
    }

    else if (event.key.code == sf::Keyboard::Down) {
        if (m_optionIndex < m_options.size() - 1) m_optionIndex++;
        else m_optionIndex = 0;

        update_option_text();
    }

    if (event.key.code == sf::Keyboard::Return)
    {
        if (m_optionIndex == PLAY) {
            request_stack_pop();
            request_stack_push(states::GAME);
        } else if (m_optionIndex == EXIT) {
            request_stack_pop();
        }
    }
}

