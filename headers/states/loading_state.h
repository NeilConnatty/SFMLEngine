//
// Created by Neil Connatty on 2016-12-01.
//

#ifndef SFMLENGINE_LOADING_STATE_H
#define SFMLENGINE_LOADING_STATE_H

#include "state.h"
#include "loading_task.h"

class loading_state : public state
{
public:
                        loading_state (state_stack& stack, context cntxt);

    virtual void        draw ();
    virtual bool        update (sf::Time dt);
    virtual bool        handle_event (const sf::Event& event);

    void                set_completion (float percent);

private:
    sf::Text            m_loadingText;
    sf::RectangleShape  m_progressBarBackground;
    sf::RectangleShape  m_progressBar;
    loading_task        m_loadingTask;
};


#endif //SFMLENGINE_LOADING_STATE_H
