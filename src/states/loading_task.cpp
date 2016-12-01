//
// Created by Neil Connatty on 2016-12-01.
//

#include "loading_task.h"
#include <SFML/System/Lock.hpp>

loading_task::loading_task () :
        m_thread(&loading_task::run_task, this),
        m_finished(false),
        m_elapsedTime(),
        m_mutex()
{
}

void loading_task::execute ()
{
    m_thread.launch();
}

bool loading_task::is_finished ()
{
    sf::Lock lock(m_mutex);
    return m_finished;
}

float loading_task::get_completion()
{
    sf::Lock lock(m_mutex);
    return m_elapsedTime.getElapsedTime().asSeconds() / 10.f;
}

void loading_task::run_task ()
{
    bool ended = false;

    while (!ended)
    {
        sf::Lock lock(m_mutex);
        if (m_elapsedTime.getElapsedTime().asSeconds() >= 10.f)
            ended = true;
    }

    {
        sf::Lock lock(m_mutex);
        m_finished = true;
    }
}