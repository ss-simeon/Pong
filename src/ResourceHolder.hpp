#pragma once

#include <map>
#include <memory>
#include <cassert>
#include <string>

namespace Fonts
{
	enum ID { fps_font };
}

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void load(Identifier id, const std::string& filename);

	template <typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter& second_param);
	
	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;

private:
	std::map<Identifier, std::unique_ptr<Resource>> m_resource_map;
};

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
	{
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	}

	auto inserted = m_resource_map.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& second_param)
{
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, second_param))
	{
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename + second_param);
	}

	auto inserted = m_resource_map.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	auto found = m_resource_map.find(id);
	assert(found != m_resource_map.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = m_resource_map.find(id);
	assert(found != m_resource_map.end());

	return *found->second;
}