//
// Created by Neil Connatty on 2016-12-01.
//

#include "loading_state.h"
#include "utility.h"

loading_state::loading_state(state_stack &stack, context cntxt) :
        state(stack, cntxt)
{
    sf::Font& font = cntxt.fonts->get(fonts::DEFAULT);
    sf::RenderWindow* window = cntxt.window;
    sf::Vector2f viewSize = window->getView().getSize();

    m_loadingText.setFont(font);
    m_loadingText.setString("Loading Resources");
    utility::centre_origin(m_loadingText);
    m_loadingText.setPosition(viewSize.x / 2u, viewSize.y / 2u + 50);

    m_progressBarBackground.setFillColor(sf::Color::White);
    m_progressBarBackground.setSize(sf::Vector2f(viewSize.x - 20, 10));
    m_progressBarBackground.setPosition(10, m_loadingText.getPosition().y + 40);

    m_progressBar.setFillColor(sf::Color(100,100,100));
    m_progressBar.setSize(sf::Vector2f(200, 10));
    m_progressBar.setPosition(m_progressBarBackground.getPosition());

    set_completion(0.f);

    m_loadingTask.execute();
}

void loading_state::set_completion (float percent)
{
    if (percent > 1.f) percent = 1.f;

    m_progressBar.setSize(sf::Vector2f(m_progressBarBackground.getSize().x * percent,
                                       m_progressBar.getSize().y));
}

void loading_state::draw ()
{
    sf::RenderWindow* window = get_context().window;
    window->setView(window->getDefaultView());

    window->draw(m_loadingText);
    window->draw(m_progressBarBackground);
    window->draw(m_progressBar);
}

bool loading_state::update (sf::Time dt)
{
    if (m_loadingTask.is_finished()) {
        request_stack_pop();
        request_stack_push(states::GAME);
    } else {
        set_completion(m_loadingTask.get_completion());
    }
    return true;
}

bool loading_state::handle_event (const sf::Event &event)
{
    return true;
}