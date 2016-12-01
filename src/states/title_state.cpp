//
// Created by Neil Connatty on 2016-11-29.
//

#include "states/title_state.h"
#include "utility.h"

title_state::title_state (state_stack &stack, state::context cntxt)  :
        state(stack, cntxt),
        m_backgroundSprite(cntxt.textures->get(textures::TITLE_SCREEN)),
        m_text(),
        m_showText(true),
        m_textEffectTime(sf::Time::Zero)
{
    m_text.setFont(cntxt.fonts->get(fonts::DEFAULT));
    m_text.setString("Press any key to play");
    utility::centre_origin(m_text);
    m_text.setPosition(cntxt.window->getView().getSize() / 2.f);
}

void title_state::draw ()
{
    sf::RenderWindow& window = *get_context().window;
    window.draw(m_backgroundSprite);

    if (m_showText)
        window.draw(m_text);
}

bool title_state::handle_event (const sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        request_stack_pop();
        request_stack_push(states::MENU);
    }

    return true;
}

bool title_state::update (sf::Time dt)
{
    m_textEffectTime += dt;

    if (m_textEffectTime >= sf::seconds(0.5f))
    {
        m_showText = !m_showText;
        m_textEffectTime = sf::Time::Zero;
    }

    return true;
}

