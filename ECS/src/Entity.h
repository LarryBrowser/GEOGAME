#include <iostream>
#include <string>
#include "Components.h"

class Entity {
	std::string  m_tag{ "default" };
	bool         m_active{ true };
	const        size_t m_id{};
public:
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CShape> cShape;
	std::shared_ptr<CCollusion> cCollusion;
	std::shared_ptr<CInput> cInput;
	std::shared_ptr<CScore> cScore;
	std::shared_ptr<CLifeSpan> cLifeSpan;
	
	Entity(size_t id, const std::string& tag);

	const std::string& tag() const;
	bool active();
	void kill() { m_active = false; }
};