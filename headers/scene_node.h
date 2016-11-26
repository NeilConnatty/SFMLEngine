//
// Created by Neil Connatty on 2016-11-10.
//

#ifndef SFMLENGINE_SCENE_NODE_H
#define SFMLENGINE_SCENE_NODE_H

#include <vector>
#include "SFML/Graphics.hpp"
#include "command.h"
#include "command_queue.h"

struct command;

class scene_node : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
    typedef std::unique_ptr<scene_node> ptr;

public:
    scene_node ();

    void attach_child (ptr child);
    ptr detach_child (const scene_node &node);

    void update (sf::Time dt);

    sf::Vector2f get_world_position () const;
    sf::Transform get_world_transform () const;

    virtual unsigned int get_category () const;
    void on_command (const command &com, sf::Time dt);

private:
    virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void draw_current (sf::RenderTarget &target, sf::RenderStates states) const;
    void draw_children (sf::RenderTarget &target, sf::RenderStates states) const;

    virtual void update_current (sf::Time dt);
    void update_children (sf::Time dt);



private:
    std::vector<ptr> m_children;
    scene_node* m_parent;
};


#endif //SFMLENGINE_SCENE_NODE_H
