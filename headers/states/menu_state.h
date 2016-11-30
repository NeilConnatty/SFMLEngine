//
// Created by Neil Connatty on 2016-11-30.
//

#ifndef SFMLENGINE_MENU_STATE_H
#define SFMLENGINE_MENU_STATE_H


#include <vector>
#include "state.h"

class menu_state : public state
{
public:
                                menu_state (state_stack& stack, state::context cntxt);

    virtual void                draw ();
    virtual bool                update (sf::Time dt);
    virtual bool                handle_event (const sf::Event& event);

private:
    void                        update_option_text ();

private:
    enum options
    {
        PLAY,
        EXIT
    };

    std::vector<sf::Text>       m_options;
    std::size_t                 m_optionIndex;
};


#endif //SFMLENGINE_MENU_STATE_H
