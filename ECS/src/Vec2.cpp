#include "Vec2.h"
Vec2::Vec2() = default;
Vec2::Vec2(float xin, float yin): x(xin), y(yin)
{}

bool Vec2::operator==(const Vec2 & rhs) const
{
	return (x == rhs.x) && (y == rhs.y);
}

bool Vec2::operator!=(const Vec2& rhs) const
{
	return !((x == rhs.x) && (y == rhs.y));
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const Vec2& rhs) const
{
	return Vec2(x * rhs.x, y * rhs.y);
}

Vec2 Vec2::operator/(const Vec2& rhs) const
{
	return Vec2(x / rhs.x, y / rhs.y);
}

void Vec2::operator+=(const Vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;
}

void Vec2::operator-=(const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}	

void Vec2::operator*=(const Vec2& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
}

void Vec2::operator/=(const Vec2& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
}

float Vec2::length(const Vec2& in) const
{
	return ((x - in.x) * (x - in.x)) + ((y - in.y) * (y - in.y));
}

void Vec2::normalize()
{
	float len = sqrt((x * x) + (y * y));
	x /= len;
	y /= len;
}

void Vec2::print()
{
	std::cout << "The x coord is: " << x << " and the y coord is: " << y << '\n';
}
