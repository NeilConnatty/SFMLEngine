//
// Created by Neil Connatty on 2016-11-27.
//

#ifndef SFMLENGINE_STATE_STACK_H
#define SFMLENGINE_STATE_STACK_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include "state.h"
#include "state_identifiers.h"

#include <vector>
#include <map>
#include <functional>

namespace sf
{
    class Event;
    class RenderWindow;
}

class state_stack : private sf::NonCopyable
{
public:
    enum action
    {
        PUSH,
        POP,
        CLEAR
    };

public:
    explicit                state_stack (state::context cntxt);

    template <typename T>
    void                    register_state (states::ID stateID);

    void                    update (sf::Time dt);
    void                    draw ();
    void                    handle_event (const sf::Event& event);

    void                    push_state (states::ID stateID);
    void                    pop_state ();
    void                    clear_states ();

    bool                    is_empty () const;

private:
    state::ptr              create_state (states::ID stateID);
    void                    apply_pending_changes ();

private:
    struct pending_change
    {
        explicit pending_change (action act, states::ID stateID = states::NONE);

        action act;
        states::ID stateID;
    };

private:
    std::vector<state::ptr>                             m_stack;
    std::vector<pending_change>                         m_pendingList;
    state::context                                      m_context;
    std::map<states::ID, std::function<state::ptr()>>   m_factories;
};

template <typename T>
void state_stack::register_state (states::ID stateID)
{
    m_factories[stateID] = [this] ()
    {
        return state::ptr(new T(*this, m_context));
    };
}


#endif //SFMLENGINE_STATE_STACK_H
