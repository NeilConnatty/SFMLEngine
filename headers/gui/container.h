//
// Created by Neil Connatty on 2016-12-05.
//

#ifndef SFMLENGINE_CONTAINER_H
#define SFMLENGINE_CONTAINER_H

#include <vector>
#include "component.h"

namespace gui
{
    class container : public component
    {
    public:
        typedef std::shared_ptr<container> ptr;

    public:
                                            container ();

        void                                pack (component::ptr cmpnt);
        virtual void                        handle_event (const sf::Event& event);

        virtual bool                        is_selectable () const;

    private:
        virtual void                        draw (sf::RenderTarget& target, sf::RenderStates states) const;

        bool                                has_selection () const;
        void                                select (std::size_t index);
        void                                select_previous ();
        void                                select_next ();

    private:
        std::vector<component::ptr>         m_children;
        int                                 m_selectedChild;
    };
}


#endif //SFMLENGINE_CONTAINER_H
