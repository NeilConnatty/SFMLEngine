//
// Created by Neil Connatty on 2016-11-03.
//

#ifndef SFMLENGINE_AIRCRAFT_H
#define SFMLENGINE_AIRCRAFT_H

#include "entity.h"

class aircraft : public entity
{
public:
    enum type {
        EAGLE,
        RAPTOR,
    };

public:
    explicit aircraft (aircraft::type m_type);

private:
    type _type;
};


#endif //SFMLENGINE_AIRCRAFT_H
