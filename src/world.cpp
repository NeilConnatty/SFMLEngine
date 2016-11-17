//
// Created by Neil Connatty on 2016-11-15.
//

#include <sprite_node.h>
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
    // initiate layer and scene graphs
    for (std::size_t i=0; i<LAYER_COUNT; ++i) {
        scene_node::ptr layer(new scene_node());
        _sceneLayers[i] = layer.get();

        _sceneGraph.attach_child(std::move(layer));
    }

    sf::Texture& desert = _textures.get(textures::DESERT);
    sf::IntRect desertRect(_worldBounds);
    desert.setRepeated(true);

    scene_node::ptr backgroundSprite(new sprite_node(desert, desertRect));
    backgroundSprite->setPosition(_worldBounds.left, _worldBounds.top);
    _sceneLayers[BACKGROUND]->attach_child(std::move(backgroundSprite));

    scene_node::ptr leader(new aircraft(aircraft::EAGLE, _textures));
    _playerAircraft = (aircraft*) leader.get();
    _playerAircraft->setPosition(_spawnPosition);
    _playerAircraft->set_velocity(40.f, _scrollSpeed);
    _sceneLayers[AIR]->attach_child(std::move(leader));

    scene_node::ptr leftEscort(new aircraft(aircraft::RAPTOR, _textures));
    leftEscort->setPosition(-80.f, 50.f);
    _playerAircraft->attach_child(std::move(leftEscort));
    scene_node::ptr rightEscort(new aircraft(aircraft::RAPTOR, _textures));
    rightEscort->setPosition(80.f, 50.f);
    _playerAircraft->attach_child(std::move(rightEscort));
}

void world::draw ()
{
    _window.setView(_worldView);
    _window.draw(_sceneGraph);
}

void world::update(sf::Time deltaTime)
{
    _worldView.move(0.f, _scrollSpeed * deltaTime.asSeconds());

    sf::Vector2f position = _playerAircraft->get_world_position();
    sf::Vector2f velocity = _playerAircraft->get_velocity();

    if (position.x <= _worldBounds.left+150 || position.x >= _worldBounds.left+_worldBounds.width-150) {
        velocity.x = -velocity.x;
        _playerAircraft->set_velocity(velocity);
    }

    _sceneGraph.update(deltaTime);
}