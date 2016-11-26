//
// Created by Neil Connatty on 2016-10-28.
//

#ifndef SFMLENGINE_RESOURCE_HOLDER_H
#define SFMLENGINE_RESOURCE_HOLDER_H

#include <string>
#include <map>
#include <assert.h>

/// template class definition ///
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
    void insert_resource (identifier id, std::unique_ptr<resource> res);

private:
    std::map<identifier, std::unique_ptr<resource>> m_resource_map;
};

/// template function definitions ///
template <typename resource, typename identifier>
void resource_holder<resource, identifier>::load (identifier id, const std::string &filename)
{
    std::unique_ptr<resource> res(new resource());
    if (!res->loadFromFile(filename))
        throw std::runtime_error("resource_holder::load - failed to load " + filename);

    insert_resource(id, std::move(res));
}

template <typename resource, typename identifier>
template <typename parameter>
void resource_holder<resource, identifier>::load (identifier id, const std::string &filename, const parameter &second_param)
{
    std::unique_ptr<resource> res(new resource());
    if (!res->loadFromFile(filename, second_param))
        throw std::runtime_error("resource_holder::load - failed to load " + filename);

    insert_resource(id, std::move(res));
}

template <typename resource, typename identifier>
resource& resource_holder<resource, identifier>::get (identifier id)
{
    auto found = m_resource_map.find(id);
    assert(found != m_resource_map.end());

    return *found->second;
}

template <typename resource, typename identifier>
const resource& resource_holder<resource, identifier>::get (identifier id) const
{
    auto found = m_resource_map.find(id);
    assert(found != m_resource_map.end());

    return *found->second;
}

template <typename resource, typename identifier>
void resource_holder<resource, identifier>::insert_resource (identifier id, std::unique_ptr<resource> res)
{
    auto inserted = m_resource_map.insert(std::make_pair(id, std::move(res)));
    assert(inserted.second);
}

#endif //SFMLENGINE_RESOURCE_HOLDER_H
