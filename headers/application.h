//
// Created by Neil Connatty on 2016-11-27.
//

#ifndef SFMLENGINE_APPLICATION_H
#define SFMLENGINE_APPLICATION_H

#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

#include "states/state_stack.h"
#include "player.h"

#define PATH_TO_PROJECT_ROOT "../"

class application
{
public:
                        application ();
    void                run ();

private:
    void                register_states ();
    void                process_input ();
    void                update (sf::Time dt);
    void                render ();

    void                update_statistics (sf::Time dt);

private:
    void                load_textures ();
    void                load_fonts ();

private:
    static sf::Time     TIME_PER_FRAME;

    state_stack         m_stack;

    sf::RenderWindow    m_window;
    player              m_player;
    font_holder         m_fonts;
    texture_holder      m_textures;

    sf::Text            m_statisticsText;
    sf::Time            m_statisticsTimeUpdate;
    std::time_t         m_statisticsNumFrames;

    bool                m_isPaused;
};


#endif //SFMLENGINE_APPLICATION_H
