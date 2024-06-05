#include "Vec2.h"
#include "SFML/Graphics.hpp"
class CTransform {
public:
	Vec2 pos{ 0.0f,0.0f };
	Vec2 velocity{ 0.0f,0.0f };
	float angle{};
	bool has{ false };
	CTransform() {}
	CTransform(const Vec2& p, const Vec2& v, float a)
		: pos(p), velocity(v), angle(a) {}
};

class CShape {
public:
	sf::CircleShape circle;
	bool has{ false };
	CShape() {}
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
	bool has{ false };
	CCollusion() {}
	CCollusion(float r)
		: radius(r) {}
};

class CScore {
public:
	int score{};
	bool has{ false };
	CScore() {}
	CScore(int s)
		: score(s) {}
};

class CLifeSpan {
public:
	int remaining{};
	int total{};
	bool has{ false };
	CLifeSpan() {}
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
	bool has{ false };
	CInput() = default;
};
