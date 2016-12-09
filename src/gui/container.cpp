//
// Created by Neil Connatty on 2016-12-05.
//

#include "gui/container.h"

using namespace gui;

container::container () :
        m_children(),
        m_selectedChild(-1)
{
}

void container::pack (component::ptr cmpnt)
{
    m_children.push_back(cmpnt);

    if (!has_selection() && cmpnt->is_selectable()) {
        select(m_children.size() - 1);
    }
}

void container::handle_event (const sf::Event &event)
{
    if (has_selection() && m_children[m_selectedChild]->is_active())
    {
        m_children[m_selectedChild]->handle_event(event);
    }
    else if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::W
            || event.key.code == sf::Keyboard::Up)
        {
            select_previous();
        }
        else if (event.key.code == sf::Keyboard::S
                || event.key.code == sf::Keyboard::Down)
        {
            select_next();
        }
        else if (event.key.code == sf::Keyboard::Return
                || event.key.code == sf::Keyboard::Space)
        {
            if (has_selection())
                m_children[m_selectedChild]->activate();
        }
    }
}

bool container::is_selectable () const
{
    return false;
}

bool container::has_selection() const
{
    return m_selectedChild >= 0;
}

void container::select (std::size_t index)
{
    if (m_children[index]->is_selectable())
    {
        if (has_selection())
            m_children[m_selectedChild]->deselect();

        m_children[index]->select();
        m_selectedChild = index;
    }
}

void container::select_next ()
{
    if (!has_selection())
        return;

    int next = m_selectedChild;
    do {
        next = (next + 1) % m_children.size();
    } while (!m_children[next]->is_selectable());

    select(next);
}

void container::select_previous ()
{
    if (!has_selection())
        return;

    int prev = m_selectedChild;
    do {
        prev = (prev + m_children.size() - 1) % m_children.size();
    } while (!m_children[prev]->is_selectable());

    select(prev);
}

void container::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (component::ptr child : m_children)
    {
        target.draw(*child, states);
    }
}