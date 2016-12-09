//
// Created by Neil Connatty on 2016-12-05.
//

#include "gui/component.h"

using namespace gui;

component::component () :
        m_isSelected(false),
        m_isActive(false)
{
}

component::~component()
{
}

bool component::is_selected() const
{
    return m_isSelected;
}

void component::select()
{
    m_isSelected = true;
}

void component::deselect()
{
    m_isSelected = false;
}

bool component::is_active() const
{
    return m_isActive;
}

void component::activate()
{
    m_isActive = true;
}

void component::deactivate()
{
    m_isActive = false;
}