//
// Created by Neil Connatty on 2016-11-30.
//

#ifndef SFMLENGINE_PAUSE_STATE_H
#define SFMLENGINE_PAUSE_STATE_H

#include "state.h"

class pause_state : public state
{
public:
                        pause_state (state_stack& stack, context cntxt);

    virtual void        draw ();
    virtual bool        update (sf::Time dt);
    virtual bool        handle_event (const sf::Event& event);

private:
    sf::Text            m_paused_text;
    sf::Text            m_instruction_text;
};


#endif //SFMLENGINE_PAUSE_STATE_H
