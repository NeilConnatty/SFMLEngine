//
// Created by Neil Connatty on 2016-11-28.
//

#ifndef SFMLENGINE_GAME_STATE_H
#define SFMLENGINE_GAME_STATE_H

#include "state.h"
#include "scene/world.h"
#include "player.h"

class game_state : public state
{
public:
                        game_state (state_stack& stack, context cntxt);

    virtual void        draw ();
    virtual bool        update (sf::Time dt);
    virtual bool        handle_event (const sf::Event& event);

private:
    world               m_world;
    player&             m_player;
};

#endif //SFMLENGINE_GAME_STATE_H
