//
// Created by Neil Connatty on 2016-11-30.
//

#include "states/menu_state.h"
#include "utility.h"

menu_state::menu_state (state_stack &stack, state::context cntxt) :
        state(stack, cntxt),
        m_options(),
        m_optionIndex(0),
        m_backgroundSprite()
{
    sf::Texture& texture = cntxt.textures->get(textures::TITLE_SCREEN);
    sf::Font& font = cntxt.fonts->get(fonts::DEFAULT);

    m_backgroundSprite.setTexture(texture);

    sf::Text playOption;
    playOption.setFont(font);
    playOption.setString("Play");
    utility::centre_origin(playOption);
    playOption.setPosition(cntxt.window->getView().getSize() / 2.f);
    m_options.push_back(playOption);

    sf::Text exitOption;
    exitOption.setFont(font);
    exitOption.setString("Exit");
    utility::centre_origin(exitOption);
    exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
    m_options.push_back(exitOption);

    update_option_text();
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
    sf::RenderWindow& window = *get_context().window;

    window.setView(window.getDefaultView());
    window.draw(m_backgroundSprite);

    for (sf::Text& text : m_options) {
        window.draw(text);
    }
}

bool menu_state::update (sf::Time dt)
{
    return true;
}

bool menu_state::handle_event (const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up)
        {
            if (m_optionIndex > 0) m_optionIndex--;
            else m_optionIndex = m_options.size() - 1;

            update_option_text();
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
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

    return true;
}

