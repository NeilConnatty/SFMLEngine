//
// Created by Neil Connatty on 2016-11-15.
//

#include "world.h"

world::world (sf::RenderWindow &window) :
        _window(window),
        _worldView(window.getDefaultView()),
        _textures(),
        _sceneGraph(),
        _sceneLayers(),
        _worldBounds(0.f, 0.f, _worldView.getSize().x, WORLD_SIZE),
        _spawnPosition(_worldView.getSize().x / 2.f, _worldBounds.height - _worldView.getSize().y / 2.f),
        _scrollSpeed(SCROLL_SPEED),
        _playerAircraft(nullptr)
{
    load_textures();
    build_scene();
    //Prepare the view
    _worldView.setCenter(_spawnPosition);
}

void world::load_textures ()
{
    std::string path(PATH_TO_PROJECT_ROOT);
    _textures.load(textures::EAGLE, path.append("assets/textures/Eagle.png"));
    path.assign(PATH_TO_PROJECT_ROOT);
    _textures.load(textures::RAPTOR, path.append("assets/textures/Raptor.png"));
    path.assign(PATH_TO_PROJECT_ROOT);
    _textures.load(textures::DESERT, path.append("assets/textures/Desert.png"));
}

void world::build_scene ()
{
    // TODO
}