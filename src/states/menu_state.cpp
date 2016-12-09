//
// Created by Neil Connatty on 2016-11-30.
//

#include <gui/button.h>
#include "states/menu_state.h"
#include "utility.h"

menu_state::menu_state (state_stack &stack, state::context cntxt) :
        state(stack, cntxt),
        m_guiContainer(),
        m_backgroundSprite()
{
    sf::Texture &texture = cntxt.textures->get(textures::TITLE_SCREEN);
    sf::Font &font = cntxt.fonts->get(fonts::DEFAULT);

    m_backgroundSprite.setTexture(texture);

    auto playButton = std::make_shared<gui::button>(*cntxt.fonts, *cntxt.textures);
    playButton->setPosition(100, 250);
    playButton->set_text("Play");
    playButton->set_callback([this]() {
        request_stack_pop();
        request_stack_push(states::GAME);
    });
    m_guiContainer.pack(playButton);

    auto exitButton = std::make_shared<gui::button>(*cntxt.fonts, *cntxt.textures);
    exitButton->setPosition(100, 300);
    exitButton->set_text("Exit");
    exitButton->set_callback([this]() {
        request_stack_pop();
    });
    m_guiContainer.pack(exitButton);
}

void menu_state::draw ()
{
    sf::RenderWindow& window = *get_context().window;

    window.setView(window.getDefaultView());
    window.draw(m_backgroundSprite);
    window.draw(m_guiContainer);
}

bool menu_state::update (sf::Time dt)
{
    return true;
}

bool menu_state::handle_event (const sf::Event &event)
{
    m_guiContainer.handle_event(event);
    return false;
}

