//
// Created by Neil Connatty on 2016-11-25.
//

#include "commands/command_queue.h"

void command_queue::push (const command &com)
{
    m_queue.push(com);
}

command command_queue::pop ()
{
    command ret = m_queue.front();
    m_queue.pop();
    return ret;
}

bool command_queue::is_empty () const
{
    return m_queue.empty();
}