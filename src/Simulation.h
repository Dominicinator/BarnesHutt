#pragma once
#include "Vector.h"
#include <thread>
#include <vector>
#include "Tree.h"
std::string round_to_digits(float value, int digits);
float RandomFloat(float a, float b);
struct Particle {
	float mass;
	vec2f position;
	Particle();
	Particle(vec2f pos);
};
struct Body : Particle {
	vec2f velocity;
	float density = 5000.0f; //kgm^-3
	
	//template<typename T>
	void update(Tree<Body> tree, float deltaTime);
	float getRadius();
	void print();
	void draw(float distanceScale, float radiusScale, sf::RenderWindow& targetWindow);
	void debugInfo(sf::RenderWindow& targetWindow, sf::Font font);
};
//template <int nBodies>
class Simulation {
public:
	float posRange;
	float massLower;
	float massHigher;
	unsigned int nBodies;
	float deltaTime;
	Body* bodies;
	Tree<Body> tree;
public:
	Simulation(float posrange, float masslower, float masshigher, int nbodies, float deltatime);
	void step();
	void draw(float scale, sf::RenderWindow& targetWindow);
};