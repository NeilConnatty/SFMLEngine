//
// Created by Neil Connatty on 2016-12-09.
//

#include "settings_state.h"
#include "utility.h"

settings_state::settings_state (state_stack &stack, context cntxt) :
        state(stack, cntxt),
        m_guiContainer(),
        m_backgroundSprite()
{
    sf::Texture& texture = cntxt.textures->get(textures::TITLE_SCREEN);
    m_backgroundSprite.setTexture(texture);

    add_button_label(player::MOVE_LEFT, 150.f, "Move Left", cntxt);
    add_button_label(player::MOVE_RIGHT, 200.f, "Move Right", cntxt);
    add_button_label(player::MOVE_UP, 250.f, "Move Up", cntxt);
    add_button_label(player::MOVE_DOWN, 300.f, "Move Down", cntxt);

    update_labels();

    auto backButton = std::make_shared<gui::button>(*cntxt.fonts, *cntxt.textures);
    backButton->set_text("Back");
    backButton->setPosition(100.f, 375.f);
    backButton->set_callback([this] () {
        request_stack_pop();
    });

    m_guiContainer.pack(backButton);
}

void settings_state::draw ()
{
    sf::RenderWindow* window = get_context().window;

    window->setView(window->getDefaultView());
    window->draw(m_backgroundSprite);
    window->draw(m_guiContainer);
}

bool settings_state::update (sf::Time dt)
{
    return true;
}

bool settings_state::handle_event (const sf::Event &event)
{
    bool isKeyBinding = false;
    for (std::size_t action = 0; action < player::ACTION_COUNT; action++)
    {
        if (m_bindingButtons[action]->is_active())
        {
            isKeyBinding = true;
            if (event.type == sf::Event::KeyReleased)
            {
                get_context().the_player->assign_key(static_cast<player::action>(action), event.key.code);
                m_bindingButtons[action]->deactivate();
                break;
            }
        }
    }
    if (isKeyBinding)
        update_labels();
    else
        m_guiContainer.handle_event(event);

    return false;
}

void settings_state::update_labels ()
{
    player* the_player = get_context().the_player;
    for (std::size_t action = 0; action < player::ACTION_COUNT; action++)
    {
        sf::Keyboard::Key key = the_player->get_assigned_key(static_cast<player::action>(action));
        m_bindingLabels[action]->set_text(utility::to_string(key));
    }
}

void settings_state::add_button_label(player::action act, float y, const std::string & text, context cntxt)
{
    m_bindingButtons[act] = std::make_shared<gui::button>(*cntxt.fonts, *cntxt.textures);
    m_bindingButtons[act]->set_text(text);
    m_bindingButtons[act]->setPosition(100.f, y);
    m_bindingButtons[act]->set_toggle(true);

    m_bindingLabels[act] = std::make_shared<gui::label>("", *cntxt.fonts);
    m_bindingLabels[act]->setPosition(325.f, y + 15.f);

    m_guiContainer.pack(m_bindingButtons[act]);
    m_guiContainer.pack(m_bindingLabels[act]);
}