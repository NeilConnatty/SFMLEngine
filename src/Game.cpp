//
// Created by Neil Connatty on 2016-10-27.
//

#include "Game.h"

sf::Time Game::TIME_PER_FRAME = sf::seconds(1.f/60.f);

Game::Game () : _window(sf::VideoMode(640, 480), "SFML Application"), _player()
{
    std::string path(PATH_TO_PROJECT_ROOT);
    path.append("assets/eagle.png");
    if (!_texture.loadFromFile(path)) {
        // handle texture load error
    }
    _player.setTexture(_texture);
    _player.setPosition(100.f, 100.f);
    _isMovingDown= false; _isMovingUp = false; _isMovingLeft = false; _isMovingRight = false;
}

void Game::run ()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (_window.isOpen())
    {
        process_events();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= TIME_PER_FRAME;
            process_events();
            update(TIME_PER_FRAME);
        }
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

void Game::handle_player_input (sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W) _isMovingUp = isPressed;
    if (key == sf::Keyboard::S) _isMovingDown = isPressed;
    if (key == sf::Keyboard::A) _isMovingLeft = isPressed;
    if (key == sf::Keyboard::D) _isMovingRight = isPressed;
}

void Game::update (sf::Time deltaTime)
{
    sf::Vector2f movement(0.f, 0.f);
    if (_isMovingUp) movement.y -= PLAYER_SPEED;
    if (_isMovingDown) movement.y += PLAYER_SPEED;
    if (_isMovingLeft) movement.x -= PLAYER_SPEED;
    if (_isMovingRight) movement.x += PLAYER_SPEED;

    _player.move(movement * deltaTime.asSeconds());
}

void Game::render ()
{
    _window.clear();
    _window.draw(_player);
    _window.display();
}
