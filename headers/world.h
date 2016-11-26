//
// Created by Neil Connatty on 2016-11-15.
//

#ifndef SFMLENGINE_WORLD_H
#define SFMLENGINE_WORLD_H


#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>

#include "textures.h"
#include "scene_node.h"
#include "sprite_node.h"
#include "aircraft.h"
#include "resource_holder.h"
#include "command_queue.h"

#define SCROLL_SPEED -50.0f
#define WORLD_SIZE 2000.f
#define PATH_TO_PROJECT_ROOT "../"

class world : private sf::NonCopyable
{
public:
    explicit world (sf::RenderWindow& window);
    void update (sf::Time deltaTime);
    void draw ();
    command_queue& get_command_queue ();

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
    sf::RenderWindow&                       m_window;
    sf::View                                m_worldView;
    texture_holder                          m_textures;
    scene_node                              m_sceneGraph;
    std::array<scene_node*, LAYER_COUNT>    m_sceneLayers;
    command_queue                           m_queue;

    sf::FloatRect                           m_worldBounds;
    sf::Vector2f                            m_spawnPosition;
    float                                   m_scrollSpeed;
    aircraft*                               m_playerAircraft;
};


#endif //SFMLENGINE_WORLD_H
