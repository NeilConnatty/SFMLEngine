//
// Created by Neil Connatty on 2016-11-30.
//

#ifndef SFMLENGINE_PAUSE_STATE_H
#define SFMLENGINE_PAUSE_STATE_H

#include "state.h"
#include "gui/container.h"

class pause_state : public state
{
public:
                        pause_state (state_stack& stack, context cntxt);

    virtual void        draw ();
    virtual bool        update (sf::Time dt);
    virtual bool        handle_event (const sf::Event& event);

private:
    gui::container      m_guiContainer;
};


#endif //SFMLENGINE_PAUSE_STATE_H
