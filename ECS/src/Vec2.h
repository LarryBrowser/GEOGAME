#include <iostream>
#include <math.h>
class Vec2 {
public:
	float x{};
	float y{};

	Vec2();
	Vec2(float x, float y);

	bool operator == (const Vec2& rhs) const;
	bool operator != (const Vec2& rhs) const;

	Vec2 operator + (const Vec2& rhs) const;
	Vec2 operator - (const Vec2& rhs) const;
	Vec2 operator * (const Vec2& rhs) const;
	Vec2 operator / (const Vec2& rhs) const;

	void operator += (const Vec2& rhs);
	void operator -= (const Vec2& rhs);
	void operator *= (const Vec2& rhs);
	void operator /= (const Vec2& rhs);

	float length(const Vec2& rhs) const;
	void normalize();
	void print();
};
