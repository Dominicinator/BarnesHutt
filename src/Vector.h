#pragma once
#include <cmath>
#include <iostream>
struct vec3f {
	float x, y, z;
	vec3f() :
		x(0), y(0), z(0) {}
	vec3f(float x_, float y_) :
		x(x_), y(y_), z(0) {}
	vec3f(float x_, float y_, float z_) :
		x(x_), y(y_), z(z_) {}
	const vec3f operator - () const {
		return vec3f(-x, -y, -z);
	}
	const vec3f operator + (const vec3f& v) const{
		return vec3f(x + v.x, y + v.y, z + v.z);
	}
	void operator += (const vec3f& v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}
	const vec3f operator - (const vec3f& v) const{
		return vec3f(x - v.x, y - v.y, z - v.z);
	}
	void operator -= (const vec3f& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}
	//scalar multiplication
	const vec3f operator * (const float& s) const{
		return vec3f(x*s, y*s, z*s);
	}
	//dot
	const float operator * (const vec3f& v) const{
		return x * v.x + y * v.y + z * v.z;
	}
	//scalar division
	const vec3f operator / (const float& s) const{
		return vec3f(x / s, y / s, z / s);
	}
	void operator /= (const float& s) {
		x /= s;
		y /= s;
		z /= s;
	}
	//cross
	const vec3f operator / (const vec3f& v) const{
		return vec3f(x, y, z);
	}
	const bool operator == (const vec3f& v) const {
		return (x == v.x && y == v.y && z == v.z);
	}
	const bool operator < (const float& s) const{
		return x < s && y < s && z < s;
	}
	const bool operator <= (const float& s) const {
		return x < s && y < s && z <= s;
	}
	const bool operator > (const float& s) const{
		return x > s && y > s && z > s;
	}
	const bool operator >= (const float& s) const {
		return x >= s && y >= s && z >= s;
	}
	const bool less2d(const float& s) const {
		return x < s && y < s;
	}
	const bool great2d(const float& s) const {
		return x > s && y > s;
	}
	const vec3f abs() const {
		return vec3f(std::abs(x), std::abs(y), std::abs(z));
	}
	const vec3f norm() const{
		return vec3f(x / std::sqrt(x*x + y * y + z * z), y / std::sqrt(x*x + y * y + z * z), z / std::sqrt(x*x + y * y + z * z));
	}
	const float mag2() const {
		//return inline (*this)*(*this)
		return x * x + y * y + z * z;
	}
	const float mag() const {
		return std::sqrt(x*x + y * y + z * z);
	}
	static vec3f random(float lower, float higher) {
		return vec3f(lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (higher - lower))),
					 lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (higher - lower))),
					 lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (higher - lower))));
	}
};
struct vec2f {
	float x, y;
	vec2f() :
		x(0), y(0) {}
	vec2f(float x_, float y_) :
		x(x_), y(y_) {}
	const vec2f operator - () const {
		return vec2f(-x, -y);
	}
	const vec2f operator + (const vec2f& v) const {
		return vec2f(x + v.x, y + v.y);
	}
	void operator += (const vec2f& v) {
		x += v.x;
		y += v.y;
	}
	const vec2f operator - (const vec2f& v) const {
		return vec2f(x - v.x, y - v.y);
	}
	void operator -= (const vec2f& v) {
		x -= v.x;
		y -= v.y;
	}
	//scalar multiplication
	const vec2f operator * (const float& s) const {
		return vec2f(x*s, y*s);
	}
	//dot
	const float operator * (const vec2f& v) const {
		return x * v.x + y * v.y;
	}
	//scalar division
	const vec2f operator / (const float& s) const {
		return vec2f(x / s, y / s);
	}
	void operator /= (const float& s) {
		x /= s;
		y /= s;
	}
	//cross
	const vec2f operator / (const vec2f& v) const {
		return vec2f(x, y);
	}
	const bool operator == (const vec2f& v) const {
		return (x == v.x && y == v.y);
	}
	const bool operator < (const float& s) const {
		return x < s && y < s;
	}
	const bool operator <= (const float& s) const {
		return x < s && y < s;
	}
	const bool operator > (const float& s) const {
		return x > s && y > s;
	}
	const bool operator >= (const float& s) const {
		return x >= s && y >= s;
	}
	const bool less2d(const float& s) const {
		return x < s && y < s;
	}
	const bool great2d(const float& s) const {
		return x > s && y > s;
	}
	const vec2f abs() const {
		return vec2f(std::abs(x), std::abs(y));
	}
	const vec2f norm() const {
		return vec2f(x / std::sqrt(x*x + y * y), y / std::sqrt(x*x + y * y));
	}
	const float mag2() const {
		//return inline (*this)*(*this)
		return x * x + y * y;
	}
	const float mag() const {
		return std::sqrt(x*x + y * y);
	}
	static vec2f random(float lower, float higher) {
		float x_ = lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (higher - lower)));
		float y_ = lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (higher - lower)));
		return vec2f(x_, y_);
	}
};
std::ostream& operator<<(std::ostream& stream, const vec2f & v) {
	stream << "(" << v.x << ", " << v.y << ")";
	return stream;
}
std::ostream& operator<<(std::ostream& stream, const vec3f & v) {
	stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return stream;
}