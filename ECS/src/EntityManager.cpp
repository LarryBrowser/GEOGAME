#include "EntityManager.h"

EntityManager::EntityManager() = default;

void EntityManager::update()
{
    for (auto& e : m_toAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }
    m_toAdd.clear();

    removeDeadEntities(m_entities);

    for (auto& [tag, entityVector] : m_entityMap)
    {
        removeDeadEntities(entityVector);
    }
}

std::shared_ptr<Entity>& EntityManager::addEntity(const std::string& tag)
{
    auto e = std::shared_ptr<Entity>(new Entity( m_totalEntities++, tag));
    m_toAdd.push_back(e);
    return e;
}

const EntityVector& EntityManager::getEntities()
{
    return m_entities;
}

const EntityVector& EntityManager::getEntities(const std::string& tag)
{
    return m_entityMap[tag];
}

void EntityManager::removeDeadEntities(EntityVector& vector)
{
    auto noDeadEntity = std::remove_if(vector.begin(),
           vector.end(), [](auto& e) {return !e->active(); });

    vector.erase(noDeadEntity, vector.end());
}
