//
// Created by Neil Connatty on 2016-12-05.
//

#ifndef SFMLENGINE_COMPONENT_H
#define SFMLENGINE_COMPONENT_H


#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>

namespace gui
{
    class component :   public sf::Drawable,
                        public sf::Transformable,
                        private sf::NonCopyable
    {
    public:
        typedef std::shared_ptr<component> ptr;

    public:
                        component ();
        virtual         ~component ();

        virtual bool    is_selectable () const  = 0;
        bool            is_selected () const;
        virtual void    select ();
        virtual void    deselect ();

        virtual bool    is_active () const;
        virtual void    activate ();
        virtual void    deactivate ();

        virtual void    handle_event (const sf::Event& event) = 0;

    private:
        bool            m_isSelected;
        bool            m_isActive;
    };
}


#endif //SFMLENGINE_COMPONENT_H
