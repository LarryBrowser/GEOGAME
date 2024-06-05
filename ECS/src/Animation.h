#include "Vec2.h"
#include "SFML/Graphics.hpp"
class Animation {
	sf::Sprite	m_sprite;
	int			m_frameCount{};
	int			m_currentFrame{};
	int			m_speed{};
	Vec2		m_size;
	std::string m_name;
public:
	void update();
	bool hasEnded();

	std::string& getName();
	std::string& getSize();
	std::string& getSprite();
};
