//
// Created by Neil Connatty on 2016-11-15.
//

#include <sprite_node.h>
#include <cmath>
#include "world.h"

world::world (sf::RenderWindow &window) :
        m_window(window),
        m_worldView(window.getDefaultView()),
        m_textures(),
        m_sceneGraph(),
        m_sceneLayers(),
        m_worldBounds(0.f, 0.f, m_worldView.getSize().x, WORLD_SIZE),
        m_spawnPosition(m_worldView.getSize().x / 2.f, m_worldBounds.height - m_worldView.getSize().y / 2.f),
        m_scrollSpeed(SCROLL_SPEED),
        m_playerAircraft(nullptr)
{
    load_textures();
    build_scene();
    //Prepare the view
    m_worldView.setCenter(m_spawnPosition);
}

void world::load_textures ()
{
    std::string path(PATH_TO_PROJECT_ROOT);
    m_textures.load(textures::EAGLE, path.append("assets/textures/Eagle.png"));
    path.assign(PATH_TO_PROJECT_ROOT);
    m_textures.load(textures::RAPTOR, path.append("assets/textures/Raptor.png"));
    path.assign(PATH_TO_PROJECT_ROOT);
    m_textures.load(textures::DESERT, path.append("assets/textures/Desert.png"));
}

void world::build_scene ()
{
    // initiate layer and scene graphs
    for (std::size_t i=0; i<LAYER_COUNT; ++i) {
        scene_node::ptr layer(new scene_node());
        m_sceneLayers[i] = layer.get();

        m_sceneGraph.attach_child(std::move(layer));
    }

    sf::Texture& desert = m_textures.get(textures::DESERT);
    sf::IntRect desertRect(m_worldBounds);
    desert.setRepeated(true);

    std::unique_ptr<sprite_node> backgroundSprite(new sprite_node(desert, desertRect));
    backgroundSprite->setPosition(m_worldBounds.left, m_worldBounds.top);
    m_sceneLayers[BACKGROUND]->attach_child(std::move(backgroundSprite));

    scene_node::ptr leader(new aircraft(aircraft::EAGLE, m_textures));
    m_playerAircraft = (aircraft*) leader.get();
    m_playerAircraft->setPosition(m_spawnPosition);
    m_playerAircraft->set_velocity(40.f, m_scrollSpeed);
    m_sceneLayers[AIR]->attach_child(std::move(leader));

    scene_node::ptr leftEscort(new aircraft(aircraft::RAPTOR, m_textures));
    leftEscort->setPosition(-80.f, 50.f);
    m_playerAircraft->attach_child(std::move(leftEscort));

    scene_node::ptr rightEscort(new aircraft(aircraft::RAPTOR, m_textures));
    rightEscort->setPosition(80.f, 50.f);
    m_playerAircraft->attach_child(std::move(rightEscort));
}

void world::draw ()
{
    m_window.setView(m_worldView);
    m_window.draw(m_sceneGraph);
}

command_queue& world::get_command_queue ()
{
    return m_queue;
}

void world::update(sf::Time deltaTime)
{
    m_worldView.move(0.f, m_scrollSpeed * deltaTime.asSeconds());
    m_playerAircraft->set_velocity(0.f, 0.f);

    while (!m_queue.is_empty()) {
        m_sceneGraph.on_command(m_queue.pop(), deltaTime);
    }

    sf::Vector2f velocity = m_playerAircraft->get_velocity();

    if (velocity.x != 0.f && velocity.y != 0.f) {
        m_playerAircraft->set_velocity(velocity / std::sqrt(2.f));
    }

    m_sceneGraph.update(deltaTime);

    sf::FloatRect viewBounds(m_worldView.getCenter() - m_worldView.getSize() / 2.f, m_worldView.getSize());
    const float borderDistance = 40.f;

    sf::Vector2f position = m_playerAircraft->getPosition();
    position.x = std::max(position.x, viewBounds.left + borderDistance);
    position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
    position.y = std::max(position.y, viewBounds.top + borderDistance);
    position.y = std::max(position.y, viewBounds.top - viewBounds.height - borderDistance);
    m_playerAircraft->setPosition(position);
}