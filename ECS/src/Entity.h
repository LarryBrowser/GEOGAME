#include <iostream>
#include <string>
#include "Components.h"
#include <tuple>

class EntityManager;

typedef std::tuple<
	CTransform,
	CShape,
	CCollusion,
	CInput,
	CScore,
	CLifeSpan> ComponentTuple;
//15:36 TIMESTAMP SE SEE SESESESESESE LOOOK!!!
class Entity {
	friend class EntityManager;

	std::string		m_tag{ "default" };
	bool			m_active{ true };
	size_t			m_id{};
	ComponentTuple	m_components;
public:
	Entity(size_t id, const std::string& tag);

	size_t id() const;
	const std::string& tag() const;
	bool active();
	void kill();

	template<typename T>
	bool hasComponent() const
	{
		return getComponent<T>().has;
	}

	template<typename T, typename... TArgs>
	T& addComponent(TArgs&& ... mArgs)
	{
		auto& component = getComponent<T>();
		component = T(std::forward<TArgs>(mArgs)...);
		component.has = true;
		return component;
	}

	template<typename T>
	T& getComponent()
	{
		return std::get<T>(m_components);
	}
	template<typename T>
	const T& getComponent() const
	{
		return std::get<T>(m_components);
	}

	template<typename T>
	T& removeComponent()
	{
		getComponent<T>() = T();
	}
};