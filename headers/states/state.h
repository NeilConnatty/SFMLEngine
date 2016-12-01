//
// Created by Neil Connatty on 2016-11-27.
//

#ifndef SFMLENGINE_STATE_H
#define SFMLENGINE_STATE_H

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "state_identifiers.h"
#include "resources/textures.h"
#include "resources/fonts.h"

#include <memory>

namespace sf
{
    class RenderWindow;
}

class state_stack;
class player;

class state
{
public:
    typedef std::unique_ptr<state> ptr;
    struct context
    {
                            context     (sf::RenderWindow& window,
                                         texture_holder& textures,
                                         font_holder& fonts,
                                         player& the_player);
        sf::RenderWindow*   window;
        texture_holder*     textures;
        font_holder*        fonts;
        player*             the_player;
    };

public:
                    state (state_stack& stack, context cntxt);
    virtual         ~state ();

    virtual void    draw () = 0;
    virtual bool    update (sf::Time dt) = 0;
    virtual bool    handle_event (const sf::Event& event) = 0;

protected:
    void            request_stack_push (states::ID stateID);
    void            request_stack_pop ();
    void            request_state_clear ();

    context         get_context () const;

private:
    state_stack*    m_stack;
    context         m_context;
};

#endif //SFMLENGINE_STATE_H
