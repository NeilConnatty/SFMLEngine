//
// Created by Neil Connatty on 2016-10-28.
//

#ifndef SFMLENGINE_TEXTURE_HOLDER_H
#define SFMLENGINE_TEXTURE_HOLDER_H

#include <memory>
#include <map>
#include <SFML/Graphics/Texture.hpp>

namespace textures {
    enum ID {
        LANDSCAPE, AIRPLANE, MISSILE
    };
}

class texture_holder {
    public:
        void load(textures::ID id, const std::string &filename);
        sf::Texture &get(textures::ID id);
        const sf::Texture &get(textures::ID id) const;


    private:
        std::map<textures::ID, std::unique_ptr<sf::Texture>> _texture_map;
};


#endif //SFMLENGINE_TEXTURE_HOLDER_H
