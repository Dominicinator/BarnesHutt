#pragma once
#include <cmath>
#include <iostream>
struct vec3f {
	float x, y, z;
	vec3f();
	vec3f(float x_, float y_);
	vec3f(float x_, float y_, float z_);
	const vec3f operator - () const;
	const vec3f operator + (const vec3f& v) const{
		return vec3f(x + v.x, y + v.y, z + v.z);
	}
	void operator += (const vec3f& v);
	const vec3f operator - (const vec3f& v) const;
	void operator -= (const vec3f& v);
	//scalar multiplication
	const vec3f operator * (const float& s) const;
	//dot
	const float operator * (const vec3f& v) const;
	//scalar division
	const vec3f operator / (const float& s) const;
	void operator /= (const float& s);
	//cross
	const vec3f operator / (const vec3f& v) const;
	const bool operator == (const vec3f& v) const;
	const bool operator < (const float& s) const;
	const bool operator <= (const float& s) const;
	const bool operator > (const float& s) const;
	const bool operator >= (const float& s) const;
	const vec3f abs() const;
	const vec3f norm() const;
	const float mag2() const;
	const float mag() const;
	static vec3f random(float lower, float higher);
};
struct vec2f {
	float x, y;
	vec2f();
	vec2f(float x_, float y_);
	//negation
	const vec2f operator - () const;
	const vec2f operator + (const vec2f& v) const;
	void operator += (const vec2f& v);
	const vec2f operator - (const vec2f& v) const;
	void operator -= (const vec2f& v);
	//scalar multiplication
	const vec2f operator * (const float& s) const;
	//dot
	const float operator * (const vec2f& v) const;
	//scalar division
	const vec2f operator / (const float& s) const;
	void operator /= (const float& s);
	//cross
	const vec2f operator / (const vec2f& v) const;
	//Test for equality of two vectors
	const bool operator == (const vec2f& v) const;
	//Check if components of a vector are both less than s.
	const bool operator < (const float& s) const;
	//Check if components of a vector are both greater than or equal to s.
	const bool operator <= (const float& s) const;
	//Check if components of a vector are both greater than s.
	const bool operator > (const float& s) const;
	//Check if components of a vector are both greater than or equal to s.
	const bool operator >= (const float& s) const;
	const vec2f abs() const;
	const vec2f norm() const;
	const float mag2() const;
	const float mag() const;
	static vec2f random(float lower, float higher);
};
