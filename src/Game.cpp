//
// Created by Neil Connatty on 2016-10-27.
//

#include "Game.h"

sf::Time Game::TIME_PER_FRAME = sf::seconds(1.f/60.f);

Game::Game () :
        m_window(sf::VideoMode(640, 480), "SFML Application"),
        m_font(),
        m_statisticsText(),
        m_statisticsTimeUpdate(),
        m_statisticsNumFrames(0),
        m_world(m_window),
        m_player()
{
    std::string path(PATH_TO_PROJECT_ROOT);
    m_font.loadFromFile(path.append("assets/Sansation.ttf"));
    m_statisticsText.setFont(m_font);
    m_statisticsText.setPosition(5.f, 5.f);
    m_statisticsText.setCharacterSize(10);
}

void Game::run ()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (m_window.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            process_events();
            if (!m_isPaused)
                update(TIME_PER_FRAME);
        }

        update_statistics(elapsedTime);
        render();
    }
}

void Game::process_events ()
{
    command_queue& commands = m_world.get_command_queue();
    sf::Event event;

    while (m_window.pollEvent(event))
    {
        m_player.handle_event(event, commands);

        switch (event.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::GainedFocus:
                m_isPaused = false;
                break;
            case sf::Event::LostFocus:
                m_isPaused = true;
                break;
        }
    }

    m_player.handle_realtime_input(commands);
}

void Game::update_statistics(sf::Time deltaTime)
{
    m_statisticsTimeUpdate += deltaTime;
    m_statisticsNumFrames += 1;

    if (m_statisticsTimeUpdate >= sf::seconds(1.f))
    {
        m_statisticsText.setString(
                "Frames / Second = " + std::to_string(m_statisticsNumFrames) + "\n" +
                "Time / Update = " + std::to_string(m_statisticsTimeUpdate.asMicroseconds()
                                                    / m_statisticsNumFrames) + "us"
        );
        m_statisticsTimeUpdate -= sf::seconds(1.f);
        m_statisticsNumFrames = 0;
    }
}

void Game::update (sf::Time deltaTime)
{
    m_world.update(deltaTime);
}

void Game::render ()
{
    m_window.clear();
    m_world.draw();

    m_window.setView(m_window.getDefaultView());
    m_window.draw(m_statisticsText);
    m_window.display();
}
