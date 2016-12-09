//
// Created by Neil Connatty on 2016-11-30.
//

#include <utility.h>
#include <gui/button.h>
#include <iostream>
#include <gui/label.h>
#include "states/pause_state.h"

pause_state::pause_state(state_stack &stack, context cntxt) :
        state(stack, cntxt),
        m_guiContainer()
{
    auto pauseLabel = std::make_shared<gui::label>("Paused", *cntxt.fonts);
    pauseLabel->setPosition(100, 200);
    m_guiContainer.pack(pauseLabel);

    auto resumeButton = std::make_shared<gui::button>(*cntxt.fonts, *cntxt.textures);
    resumeButton->setPosition(100, 250);
    resumeButton->set_text("Resume Game");
    resumeButton->set_callback([this] () {
        request_stack_pop();
    });
    m_guiContainer.pack(resumeButton);

    auto quitButton = std::make_shared<gui::button>(*cntxt.fonts, *cntxt.textures);
    quitButton->setPosition(100, 300);
    quitButton->set_text("Return to Menu");
    quitButton->set_callback([this] () {
        request_state_clear();
        request_stack_push(states::MENU);
    });
    m_guiContainer.pack(quitButton);
}

void pause_state::draw ()
{
    sf::RenderWindow& window = *get_context().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));

    window.draw(backgroundShape);
    window.draw(m_guiContainer);
}

bool pause_state::update (sf::Time dt)
{
    return false;
}

bool pause_state::handle_event (const sf::Event &event)
{
    m_guiContainer.handle_event(event);
    return false;
}