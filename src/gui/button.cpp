//
// Created by Neil Connatty on 2016-12-08.
//

#include <utility.h>
#include "gui/button.h"

using namespace gui;

button::button (font_holder &fonts, texture_holder &textures) :
        m_normalTexture(textures.get(textures::BUTTON_NORMAL)),
        m_pressedTexture(textures.get(textures::BUTTON_PRESSED)),
        m_selectedTexture(textures.get(textures::BUTTON_SELECTED)),
        m_text("", fonts.get(fonts::DEFAULT), 16),
        m_sprite(),
        m_isToggle(false),
        m_callback()
{
    m_sprite.setTexture(m_normalTexture);
    utility::centre_origin(m_text);

    sf::FloatRect bounds = m_sprite.getLocalBounds();
    m_text.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

void button::set_callback (callback clbk)
{
    m_callback = std::move(clbk);
}

void button::set_text (const std::string &text)
{
    m_text.setString(text);
}

void button::set_toggle (bool flag)
{
    m_isToggle = flag;
}

bool button::is_selectable () const
{
    return true;
}

void button::select ()
{
    component::select();
    m_sprite.setTexture(m_selectedTexture);
}

void button::deselect ()
{
    component::deselect();
    m_sprite.setTexture(m_normalTexture);
}

void button::activate ()
{
    component::activate();
    if (m_isToggle)
        m_sprite.setTexture(m_pressedTexture);
    if (m_callback)
        m_callback();
    if (!m_isToggle)
        deactivate();
}

void button::deactivate ()
{
    component::deactivate();
    if (m_isToggle)
    {
        if (is_selected())
            m_sprite.setTexture(m_selectedTexture);
        else
            m_sprite.setTexture(m_normalTexture);
    }
}

void button::handle_event (const sf::Event &event)
{
}

void button::draw (sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
    target.draw(m_text, states);
}