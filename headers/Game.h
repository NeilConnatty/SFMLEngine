//
// Created by Neil Connatty on 2016-10-27.
//

#ifndef SFMLENGINE_GAME_H
#define SFMLENGINE_GAME_H
#include <SFML/Graphics.hpp>

#define PLAYER_SPEED 100.f
#define PATH_TO_PROJECT_ROOT "../../"

class Game
{
public:
    Game ();
    void run ();

private:
    void process_events ();
    void update (sf::Time deltaTime);
    void render ();
    void handle_player_input (sf::Keyboard::Key key, bool isPressed);

private:
    static sf::Time TIME_PER_FRAME;
    sf::RenderWindow _window;
    sf::Sprite _player;
    sf::Texture _texture;
    bool _isMovingUp;
    bool _isMovingDown;
    bool _isMovingLeft;
    bool _isMovingRight;
};


#endif //SFMLENGINE_GAME_H
