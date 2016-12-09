//
// Created by Neil Connatty on 2016-12-08.
//

#ifndef SFMLENGINE_LABEL_H
#define SFMLENGINE_LABEL_H

#include <string>

#include <resources/fonts.h>
#include "component.h"

namespace gui
{
    class label : public gui::component
    {
    public:
        typedef std::shared_ptr<label> ptr;

    public:
                            label(const std::string &text, const font_holder &fonts);

        virtual bool        is_selectable() const;
        virtual void        handle_event (sf::Event& event);

        virtual void        draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void                set_text(const std::string &text);

    private:
        sf::Text            m_text;
    };
}


#endif //SFMLENGINE_LABEL_H
