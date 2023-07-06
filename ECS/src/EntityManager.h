#include "Entity.h"
#include <vector>
#include <map>
#include <string>
typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map   <std::string, EntityVector> EntityMap;

class EntityManager {
	EntityVector	m_entities;
	EntityVector	m_toAdd;
	EntityMap		m_entityMap;
	size_t			m_totalEntities{};
public:
	EntityManager();
	void update();
	std::shared_ptr<Entity>& addEntity(const std::string& tag);
	const EntityVector& getEntities();
	const EntityVector& getEntities(const std::string& tag);
	void removeDeadEntities(EntityVector& entities);
};