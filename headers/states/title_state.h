//
// Created by Neil Connatty on 2016-11-29.
//

#ifndef SFMLENGINE_TITLE_STATE_H
#define SFMLENGINE_TITLE_STATE_H

#include "states/state.h"
#include "states/state_stack.h"

class title_state : public state
{
public:
                    title_state (state_stack& stack, state::context cntxt);

    virtual void    draw ();
    virtual bool    update (sf::Time dt);
    virtual bool    handle_event (const sf::Event& event);

private:
    sf::Sprite      m_backgroundSprite;
    sf::Text        m_text;

    bool            m_showText;
    sf::Time        m_textEffectTime;
};


#endif //SFMLENGINE_TITLE_STATE_H
