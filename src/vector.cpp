#include "Vector.h"

vec3f::vec3f() :
	x(0), y(0), z(0) {}
vec3f::vec3f(float x_, float y_) :
	x(x_), y(y_), z(0) {}
vec3f::vec3f(float x_, float y_, float z_) :
	x(x_), y(y_), z(z_) {}

const vec3f vec3f::operator-() const
{
	return vec3f(-x, -y, -z);
}

void vec3f::operator+=(const vec3f & v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

const vec3f vec3f::operator-(const vec3f & v) const
{
	return vec3f(x - v.x, y - v.y, z - v.z);
}

void vec3f::operator-=(const vec3f & v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

const vec3f vec3f::operator*(const float & s) const
{
	return vec3f(x*s, y*s, z*s);
}

const float vec3f::operator*(const vec3f & v) const
{
	return x * v.x + y * v.y + z * v.z;
}

const vec3f vec3f::operator/(const float & s) const
{
	return vec3f(x / s, y / s, z / s);
}

void vec3f::operator/=(const float & s)
{
	x /= s;
	y /= s;
	z /= s;
}

const vec3f vec3f::abs() const
{
	return vec3f(std::abs(x), std::abs(y), std::abs(z));
}

const vec3f vec3f::norm() const
{
	return vec3f(x / std::sqrt(x*x + y * y + z * z), y / std::sqrt(x*x + y * y + z * z), z / std::sqrt(x*x + y * y + z * z));
}

const float vec3f::mag2() const
{
	//return inline (*this)*(*this)
	return x * x + y * y + z * z;
}

const float vec3f::mag() const
{
	return std::sqrt(x*x + y * y + z * z);
}

vec3f vec3f::random(float lower, float higher)
{
	return vec3f(lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (higher - lower))),
		lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (higher - lower))),
		lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (higher - lower))));
}

vec2f::vec2f() :
	x(0), y(0) {}

vec2f::vec2f(float x_, float y_) :
	x(x_), y(y_) {}

const vec2f vec2f::operator-() const
{
	return vec2f(-x, -y);
}

const vec2f vec2f::operator+(const vec2f & v) const
{
	return vec2f(x + v.x, y + v.y);
}

void vec2f::operator+=(const vec2f & v)
{
	x += v.x;
	y += v.y;
}

const vec2f vec2f::operator-(const vec2f & v) const
{
	return vec2f(x - v.x, y - v.y);
}

void vec2f::operator-=(const vec2f & v)
{
	x -= v.x;
	y -= v.y;
}

const vec2f vec2f::operator*(const float & s) const
{
	return vec2f(x*s, y*s);
}

const float vec2f::operator*(const vec2f & v) const
{
	return x * v.x + y * v.y;
}

const vec2f vec2f::operator/(const float & s) const
{
	return vec2f(x / s, y / s);
}

void vec2f::operator/=(const float & s)
{
	x /= s;
	y /= s;
}

const vec2f vec2f::operator/(const vec2f & v) const
{
	return vec2f(x, y);
}

const bool vec2f::operator==(const vec2f & v) const
{
	return x == v.x && y == v.y;
}

const bool vec2f::operator<(const float & s) const
{
	return x < s && y < s;
}

const bool vec2f::operator<=(const float & s) const
{
	return x <= s && y <= s;
}

const bool vec2f::operator>(const float & s) const
{
	return x > s && y > s;
}

const bool vec2f::operator>=(const float & s) const
{
	return x >= s && y >= s;
}

const vec2f vec2f::abs() const
{
	return vec2f(std::abs(x), std::abs(y));
}

const vec2f vec2f::norm() const
{
	return vec2f(x / std::sqrt(x*x + y * y), y / std::sqrt(x*x + y * y));
}

const float vec2f::mag2() const
{
	return x * x + y * y;
}

const float vec2f::mag() const
{
	return std::sqrt(x * x + y * y);
}

vec2f vec2f::random(float lower, float higher)
{
	float x_ = lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (higher - lower)));
	float y_ = lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (higher - lower)));
	return vec2f(x_, y_);
}
std::ostream & operator<<(std::ostream & stream, const vec2f & v)
{
	stream << "(" << v.x << ", " << v.y << ")";
	return stream;
}
std::ostream & operator<<(std::ostream & stream, const vec3f & v)
{
	stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return stream;
}
