//
// Created by Neil Connatty on 2016-10-27.
//

#include "Game.h"

sf::Time Game::TIME_PER_FRAME = sf::seconds(1.f/60.f);

Game::Game () :
        _window(sf::VideoMode(640, 480), "SFML Application"),
        _world(_window),
        _statisticsNumFrames(0)
{
    std::string path(PATH_TO_PROJECT_ROOT);
    _font.loadFromFile(path.append("assets/Sansation.ttf"));
    _statisticsText.setFont(_font);
    _statisticsText.setPosition(5.f, 5.f);
    _statisticsText.setCharacterSize(10);
}

void Game::run ()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (_window.isOpen())
    {
        process_events();
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            process_events();
            update(TIME_PER_FRAME);
        }

        update_statistics(elapsedTime);
        render();
    }
}

void Game::process_events ()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handle_player_input(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handle_player_input(event.key.code, false);
                break;
            case sf::Event::Closed:
                _window.close();
                break;
        }
    }
}

void Game::update_statistics(sf::Time deltaTime)
{
    _statisticsTimeUpdate += deltaTime;
    _statisticsNumFrames += 1;

    if (_statisticsTimeUpdate >= sf::seconds(1.f))
    {
        _statisticsText.setString(
                "Frames / Second = " + std::to_string(_statisticsNumFrames) + "\n" +
                "Time / Update = " + std::to_string(_statisticsTimeUpdate.asMicroseconds() / _statisticsNumFrames) + "us"
        );
        _statisticsTimeUpdate -= sf::seconds(1.f);
        _statisticsNumFrames = 0;
    }
}

void Game::handle_player_input (sf::Keyboard::Key key, bool isPressed)
{
}

void Game::update (sf::Time deltaTime)
{
    _world.update(deltaTime);
}

void Game::render ()
{
    _window.clear();
    _world.draw();

    _window.setView(_window.getDefaultView());
    _window.draw(_statisticsText);
    _window.display();
}
