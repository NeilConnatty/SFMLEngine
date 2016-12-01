//
// Created by Neil Connatty on 2016-12-01.
//

#ifndef SFMLENGINE_LOADING_TASK_H
#define SFMLENGINE_LOADING_TASK_H


#include <SFML/System/Thread.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Mutex.hpp>

class loading_task
{
public:
                    loading_task ();

    void            execute ();
    bool            is_finished ();
    float           get_completion ();

private:
    void            run_task ();

private:
    sf::Thread      m_thread;
    bool            m_finished;
    sf::Clock       m_elapsedTime;
    sf::Mutex       m_mutex;
};


#endif //SFMLENGINE_LOADING_TASK_H
