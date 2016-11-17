//
// Created by Neil Connatty on 2016-11-15.
//

#ifndef SFMLENGINE_WORLD_H
#define SFMLENGINE_WORLD_H


#include <SFML/System/NonCopyable.hpp>
#include <array>

#include "textures.h"
#include "scene_node.h"
#include "aircraft.h"

#define SCROLL_SPEED -50.0f
#define WORLD_SIZE 2000.f
#define PATH_TO_PROJECT_ROOT "../../"

class world : private sf::NonCopyable
{
public:
    explicit world (sf::RenderWindow& window);
    void update (sf::Time deltaTime);
    void draw ();

private:
    void load_textures ();
    void build_scene ();

private:
    enum layer {
        BACKGROUND,
        AIR,
        LAYER_COUNT
    };

private:
    sf::RenderWindow&                       _window;
    sf::View                                _worldView;
    textures::texture_holder                _textures;
    scene_node                              _sceneGraph;
    std::array<scene_node*, LAYER_COUNT>    _sceneLayers;

    sf::FloatRect                           _worldBounds;
    sf::Vector2f                            _spawnPosition;
    float                                   _scrollSpeed;
    aircraft*                               _playerAircraft;
};


#endif //SFMLENGINE_WORLD_H
