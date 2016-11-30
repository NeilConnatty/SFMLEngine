//
// Created by Neil Connatty on 2016-11-10.
//

#include <algorithm>
#include <assert.h>
#include "scene/scene_node.h"

scene_node::scene_node () :
    m_children(),
    m_parent(nullptr)
{
}

void scene_node::attach_child (scene_node::ptr child)
{
    child->m_parent = this;
    m_children.push_back(std::move(child));
}

scene_node::ptr scene_node::detach_child (const scene_node &node)
{
    auto found = std::find_if(m_children.begin(), m_children.end(), [&] (ptr &p) -> bool {return p.get() == &node; });
    assert(found != m_children.end());

    ptr result = std::move(*found);
    result->m_parent = nullptr;
    m_children.erase(found);

    return result;
}

void scene_node::draw_children (sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const ptr& child : m_children) {
        child->draw(target, states);
    }
}

void scene_node::draw_current (sf::RenderTarget &target, sf::RenderStates states) const
{
}


void scene_node::draw (sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    draw_current(target, states);
    draw_children(target, states);
}

void scene_node::update_children (sf::Time dt)
{
    for (const ptr& child : m_children) {
        child->update(dt);
    }
}

void scene_node::update_current (sf::Time dt)
{
}

void scene_node::update (sf::Time dt)
{
    update_current(dt);
    update_children(dt);
}

sf::Transform scene_node::get_world_transform () const
{
    sf::Transform transform = sf::Transform::Identity;

    for (const scene_node* node = this; node != nullptr; node = node->m_parent) {
        transform = node->getTransform() * transform;
    }

    return transform;
}

sf::Vector2f scene_node::get_world_position () const
{
    return get_world_transform() * sf::Vector2f();
}

unsigned int scene_node::get_category () const
{
    return category::SCENE;
}

void scene_node::on_command(const command &com, sf::Time dt)
{
    if (com.category & get_category())
        com.action(*this, dt);

    for (ptr& child : m_children)
        child->on_command(com, dt);
}