//
// Created by Neil Connatty on 2016-11-25.
//

#ifndef SFMLENGINE_CATEGORY_H
#define SFMLENGINE_CATEGORY_H

namespace category
{
    enum type
    {
        NONE = 0,
        SCENE = 1 << 0,
        PLAYER_AIRCRAFT = 1 << 1,
        ALLIED_AIRCRAFT = 1 << 2,
        ENEMY_AIRCRAFT = 1 << 3,
    };
}


#endif //SFMLENGINE_CATEGORY_H
