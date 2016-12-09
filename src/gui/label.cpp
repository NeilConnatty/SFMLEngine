//
// Created by Neil Connatty on 2016-12-08.
//

#include "gui/label.h"

using namespace gui;

label::label (const std::string &text, const font_holder &fonts)  :
        m_text(text, fonts.get(fonts::DEFAULT), 16)
{
}

bool label::is_selectable () const
{
    return false;
}

void label::draw (sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_text, states);
}

void label::set_text(const std::string &text)
{
    m_text.setString(text);
}

void label::handle_event (sf::Event &event)
{
}