//
// Created by Neil Connatty on 2016-12-08.
//

#ifndef SFMLENGINE_BUTTON_H
#define SFMLENGINE_BUTTON_H

#include <resources/fonts.h>
#include <resources/textures.h>
#include "component.h"

namespace gui
{
    class button : public component
    {
    public:
        typedef std::shared_ptr<button> ptr;
        typedef std::function<void()>   callback;

    public:
                        button (font_holder& fonts, texture_holder& textures);

        void            set_callback (callback clbk);
        void            set_text (const std::string& text);
        void            set_toggle (bool flag);

        virtual bool    is_selectable () const;
        virtual void    select ();
        virtual void    deselect ();

        virtual void    activate ();
        virtual void    deactivate ();

        virtual void    handle_event (const sf::Event& event);
        virtual void    draw (sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Sprite      m_sprite;
        sf::Text        m_text;

        sf::Texture     m_normalTexture;
        sf::Texture     m_pressedTexture;
        sf::Texture     m_selectedTexture;

        bool            m_isToggle;
        callback        m_callback;

    };
}


#endif //SFMLENGINE_BUTTON_H
