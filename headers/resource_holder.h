//
// Created by Neil Connatty on 2016-10-28.
//

#ifndef SFMLENGINE_RESOURCE_HOLDER_H
#define SFMLENGINE_RESOURCE_HOLDER_H

#include <string>
#include <map>
#include <assert.h>

template <typename resource, typename identifier>
class resource_holder
{
public:
    void load (identifier id, const std::string &filename);
    template <typename parameter>
    void load (identifier id, const std::string &filename, const parameter &second_param);
    resource& get (identifier id);
    const resource& get (identifier id) const;

private:
    std::map<identifier, std::unique_ptr<resource>> _resource_map;
};

template <typename resource, typename identifier>
void resource_holder<resource, identifier>::load (identifier id, const std::string &filename)
{
    std::unique_ptr<resource> _resource(new resource());
    if (!_resource->loadFromFile(filename))
        throw std::runtime_error("resource_holder::load - failed to load " + filename);

    auto inserted = _resource_map.insert(std::make_pair(id, std::move(_resource)));
    assert(inserted.second);
}

template <typename resource, typename identifier>
template <typename parameter>
void resource_holder<resource, identifier>::load (identifier id, const std::string &filename, const parameter &second_param)
{
    std::unique_ptr<resource> _resource(new resource());
    if (!_resource->loadFromFile(filename, second_param))
        throw std::runtime_error("resource_holder::load - failed to load " + filename);

    auto inserted = _resource_map.insert(std::make_pair(id, std::move(_resource)));
    assert(inserted.second);
}

template <typename resource, typename identifier>
resource& resource_holder<resource, identifier>::get (identifier id)
{
    auto found = _resource_map.find(id);
    assert(found != _resource_map.end());

    return *found->second;
}

template <typename resource, typename identifier>
const resource& resource_holder<resource, identifier>::get (identifier id) const
{
    auto found = _resource_map.find(id);
    assert(found != _resource_map.end());

    return *found->second;
}

#endif //SFMLENGINE_RESOURCE_HOLDER_H
