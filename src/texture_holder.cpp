//
// Created by Neil Connatty on 2016-10-28.
//

#include <assert.h>
#include "texture_holder.h"

using namespace textures;

void texture_holder::load (textures::ID id, const std::string &filename)
{
    std::unique_ptr<sf::Texture> texture(new sf::Texture);
    if (!texture->loadFromFile(filename))
        std::runtime_error("texture_holder::load - failed to load " + filename);

    auto inserted = _texture_map.insert(std::make_pair(id, std::move(texture)));
    assert(inserted.second);
}

sf::Texture& texture_holder::get (textures::ID id)
{
    auto found = _texture_map.find(id);
    assert(found != _texture_map.end());

    return *found->second;
}

const sf::Texture& texture_holder::get (textures::ID id) const
{
    auto found = _texture_map.find(id);
    assert(found != _texture_map.end());

    return *found->second;
}