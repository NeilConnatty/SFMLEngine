//
// Created by Neil Connatty on 2016-10-27.
//

#ifndef SFMLENGINE_GAME_H
#define SFMLENGINE_GAME_H

#include <SFML/Graphics.hpp>
#include "scene/world.h"
#include "player.h"

#define PATH_TO_PROJECT_ROOT "../"

class Game
{
public:
                            Game ();
    void                    run ();

private:
    void                    process_events ();
    void                    update (sf::Time deltaTime);
    void                    render ();

    void                    update_statistics (sf::Time deltaTime);

private:
    static sf::Time         TIME_PER_FRAME;

    sf::RenderWindow        m_window;
    world                   m_world;
    player                  m_player;

    sf::Font                m_font;
    sf::Text                m_statisticsText;
    sf::Time                m_statisticsTimeUpdate;
    std::time_t             m_statisticsNumFrames;

    bool                    m_isPaused;
};


#endif //SFMLENGINE_GAME_H
