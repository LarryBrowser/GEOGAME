#include "Entity.h"

Entity::Entity(size_t id, const std::string& tag): m_id(id), m_tag(tag)
{
}

size_t Entity::id() const
{
	return m_id;
}

const std::string& Entity::tag() const
{
	return m_tag;
}

bool Entity::active()
{
	return m_active;
}

void Entity::kill()
{
	m_active = false;
}
