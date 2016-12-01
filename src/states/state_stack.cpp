//
// Created by Neil Connatty on 2016-11-27.
//

#include "states/state_stack.h"
#include <cassert>

state_stack::state_stack (state::context cntxt) :
        m_stack(),
        m_context(cntxt),
        m_pendingList(),
        m_factories()
{
}

state::ptr state_stack::create_state (states::ID stateID)
{
    auto found = m_factories.find(stateID);
    assert(found != m_factories.end());

    return found->second();
}

bool state_stack::is_empty () const
{
    return m_stack.empty();
}

void state_stack::draw ()
{
    for (state::ptr& state : m_stack)
        state->draw();
}

void state_stack::handle_event (const sf::Event &event)
{
    for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr)
    {
        if (!(*itr)->handle_event(event))
            return;
    }

    apply_pending_changes();
}

void state_stack::update (sf::Time dt)
{
    for (auto itr = m_stack.rbegin(); itr != m_stack.rend(); ++itr)
    {
        if (!(*itr)->update(dt))
            return;
    }

    if (!m_pendingList.empty())
        apply_pending_changes();
}

void state_stack::push_state(states::ID stateID)
{
    m_pendingList.push_back(pending_change(PUSH, stateID));
}

void state_stack::pop_state ()
{
    m_pendingList.push_back(pending_change(POP));
}

void state_stack::clear_states ()
{
    m_pendingList.push_back(pending_change(CLEAR));
}

void state_stack::apply_pending_changes ()
{
    for (pending_change change : m_pendingList)
    {
        switch (change.act)
        {
            case PUSH:
                m_stack.push_back(create_state(change.stateID));
                break;

            case POP:
                m_stack.pop_back();
                break;

            case CLEAR:
                m_stack.clear();
                break;
        }
    }

    m_pendingList.clear();
}


state_stack::pending_change::pending_change (action act, states::ID stateID) :
        act(act),
        stateID(stateID)
{
}