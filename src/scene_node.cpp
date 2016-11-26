//
// Created by Neil Connatty on 2016-11-10.
//

#include <algorithm>
#include <assert.h>
#include "scene_node.h"

scene_node::scene_node () :
    _children(),
    _parent(nullptr)
{
}

void scene_node::attach_child (scene_node::ptr child)
{
    child->_parent = this;
    _children.push_back(std::move(child));
}

scene_node::ptr scene_node::detach_child (const scene_node &node)
{
    auto found = std::find_if(_children.begin(), _children.end(), [&] (ptr &p) -> bool {return p.get() == &node; });
    assert(found != _children.end());

    ptr result = std::move(*found);
    result->_parent = nullptr;
    _children.erase(found);

    return result;
}

void scene_node::draw_children (sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const ptr& child : _children) {
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
    for (const ptr& child : _children) {
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

    for (const scene_node* node = this; node != nullptr; node = node->_parent) {
        transform = node->getTransform() * transform;
    }

    return transform;
}

sf::Vector2f scene_node::get_world_position () const
{
    return get_world_transform() * sf::Vector2f();
}