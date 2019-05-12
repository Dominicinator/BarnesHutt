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
	vec3f operator - () const {
		return vec3f(-x, -y, -z);
	}
	vec3f operator + (const vec3f& v) const{
		return vec3f(x + v.x, y + v.y, z + v.z);
	}
	void operator += (const vec3f& v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}
	vec3f operator - (const vec3f& v) const{
		return vec3f(x - v.x, y - v.y, z - v.z);
	}
	void operator -= (const vec3f& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}
	//scalar multiplication
	vec3f operator * (const float& s) const{
		return vec3f(x*s, y*s, z*s);
	}
	//dot
	float operator * (const vec3f& v) const{
		return x * v.x + y * v.y + z * v.z;
	}
	//scalar division
	vec3f operator / (const float& s) const{
		return vec3f(x / s, y / s, z / s);
	}
	void operator /= (const float& s) {
		x /= s;
		y /= s;
		z /= s;
	}
	//cross
	vec3f operator / (const vec3f& v) const{
		return vec3f(x, y, z);
	}
	bool operator == (const vec3f& v) const {
		return (x == v.x && y == v.y && z == v.z);
	}
	bool operator < (const float& s) const{
		return x < s && y < s && z < s;
	}
	bool operator <= (const float& s) const {
		return x < s && y < s && z <= s;
	}
	bool operator > (const float& s) const{
		return x > s && y > s && z > s;
	}
	bool operator >= (const float& s) const {
		return x >= s && y >= s && z >= s;
	}
	bool less2d(const float& s) const {
		return x < s && y < s;
	}
	bool great2d(const float& s) const {
		return x > s && y > s;
	}
	vec3f abs() {
		return vec3f(std::abs(x), std::abs(y), std::abs(z));
	}
	vec3f norm() {
		return vec3f(x / std::sqrt(x*x + y * y + z * z), y / std::sqrt(x*x + y * y + z * z), z / std::sqrt(x*x + y * y + z * z));
	}
	float mag2() {
		//return inline (*this)*(*this)
		return x * x + y * y + z * z;
	}
	float mag() {
		return std::sqrt(x*x + y * y + z * z);
	}
	static vec3f random(float lower, float higher) {
		return vec3f(lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (higher - lower))),
					 lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (higher - lower))),
					 lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (higher - lower))));
	}
};
struct vec2f {
	float x, y, z;
	vec2f() :
		x(0), y(0), z(0) {}
	vec2f(float x_, float y_) :
		x(x_), y(y_), z(0) {}
	vec2f(float x_, float y_, float z_) :
		x(x_), y(y_), z(z_) {}
	vec2f operator - () const {
		return vec2f(-x, -y);
	}
	vec2f operator + (const vec2f& v) const {
		return vec2f(x + v.x, y + v.y);
	}
	void operator += (const vec2f& v) {
		x += v.x;
		y += v.y;
	}
	vec2f operator - (const vec2f& v) const {
		return vec2f(x - v.x, y - v.y);
	}
	void operator -= (const vec2f& v) {
		x -= v.x;
		y -= v.y;
	}
	//scalar multiplication
	vec2f operator * (const float& s) const {
		return vec2f(x*s, y*s);
	}
	//dot
	float operator * (const vec2f& v) const {
		return x * v.x + y * v.y;
	}
	//scalar division
	vec2f operator / (const float& s) const {
		return vec2f(x / s, y / s);
	}
	void operator /= (const float& s) {
		x /= s;
		y /= s;
	}
	//cross
	vec2f operator / (const vec2f& v) const {
		return vec2f(x, y);
	}
	bool operator == (const vec2f& v) const {
		return (x == v.x && y == v.y);
	}
	bool operator < (const float& s) const {
		return x < s && y < s;
	}
	bool operator <= (const float& s) const {
		return x < s && y < s;
	}
	bool operator > (const float& s) const {
		return x > s && y > s;
	}
	bool operator >= (const float& s) const {
		return x >= s && y >= s;
	}
	bool less2d(const float& s) const {
		return x < s && y < s;
	}
	bool great2d(const float& s) const {
		return x > s && y > s;
	}
	vec2f abs() {
		return vec2f(std::abs(x), std::abs(y));
	}
	vec2f norm() {
		return vec2f(x / std::sqrt(x*x + y * y + z * z), y / std::sqrt(x*x + y * y + z * z));
	}
	float mag2() {
		//return inline (*this)*(*this)
		return x * x + y * y;
	}
	float mag() {
		return std::sqrt(x*x + y * y);
	}
	static vec2f random(float lower, float higher) {
		return vec2f(lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (higher - lower))),
			lower + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (higher - lower))));
	}
};