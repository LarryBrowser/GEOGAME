#include "Vec2.h"
#include "SFML/Graphics.hpp"
class CTransform {
public:
	Vec2 pos{ 0.0f,0.0f };
	Vec2 velocity{ 0.0f,0.0f };
	float angle{};
	CTransform(const Vec2& p, const Vec2& v, float a)
		: pos(p), velocity(v), angle(a) {}
};

class CShape {
public:
	sf::CircleShape circle;
	CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness)
		:circle(radius, points)
	{
		circle.setFillColor(fill);
		circle.setOutlineThickness(thickness);
		circle.setOutlineColor(outline);
		circle.setOrigin(radius, radius);
	}
};

class CCollusion {
public:
	float radius{};
	CCollusion(float r)
		: radius(r) {}
};

class CScore {
public:
	int score{};
	CScore(int s)
		: score(s) {}
};

class CLifeSpan {
public:
	int remaining{};
	int total{};
	CLifeSpan(int total)
		: total(total), remaining(total) {}
};

class CInput {
public:
	bool up{};
	bool right{};
	bool left{};
	bool down{};
	bool shoot{};

	CInput() = default;
};
