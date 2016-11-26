//
// Created by Neil Connatty on 2016-11-25.
//

#ifndef SFMLENGINE_COMMAND_QUEUE_H
#define SFMLENGINE_COMMAND_QUEUE_H

#include <command.h>
#include <queue>

class command_queue
{
public:
    void                    push (const command& com);
    command                 pop ();
    bool                    is_empty () const;

private:
    std::queue<command>     m_queue;
};


#endif //SFMLENGINE_COMMAND_QUEUE_H
