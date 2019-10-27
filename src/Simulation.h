#pragma once
#include "Vector.h"
#include <thread>
#include <vector>
#include "Tree.h"
std::string round_to_digits(float value, int digits)
{
	std::string s = std::to_string(value);
	std::string out = "";
	for (auto c : s) {
		if (!(c == (char)".")) {
			if (digits > 0) {
				out += c;
				digits--;
			}
		}
		else {
			out += c;
		}
	}
	return out;
}
float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}
struct Particle {
	float mass;
	vec2f position;
	Particle() :
		position(vec2f()) {}
	Particle(vec2f pos) :
		position(pos) {}
};
struct Body : Particle {
	vec2f velocity;
	float density = 5000.0f; //kgm^-3
	
	//template<typename T>
	void update(Tree<Particle> tree, float deltaTime) {
		vec2f a1 = tree.getAcceleration(position);
		//std::cout << "pos: " << position << std::endl;
		position = position + velocity * deltaTime + a1 * 0.5f*deltaTime*deltaTime;
		//std::cout << "pos: " << position << std::endl;
		vec2f a2 = tree.getAcceleration(position);
		//std::cout << "vel: " << velocity << std::endl;
		velocity = velocity + (a1 + a2)*0.5f*deltaTime;
		//std::cout << "vel: " << velocity << std::endl;
		//std::cout << "a1: " << a1 << "a2: " << a2 << std::endl;
	}
	float getRadius() {
		float volume = mass / density;
		return std::cbrt((3 / (4 * 3.14159265358979323846)) * volume);
	}
	void debug() {

	}
	void draw(float distanceScale, float radiusScale, sf::RenderWindow& targetWindow) {
		//sf::CircleShape planet(mass*radiusScale);
		float radius = getRadius();
		radius = 5.0f;
		radiusScale = 1.0f;
		//std::cout << radius * radiusScale << std::endl;
		sf::CircleShape planet(radius * radiusScale);
		planet.setPosition(position.x * distanceScale - radius * radiusScale - 400.0f, position.y * distanceScale - radius * radiusScale - 400.0f);
		planet.setFillColor(sf::Color::White);
		targetWindow.draw(planet);
	}
	void debugInfo(sf::RenderWindow& targetWindow, sf::Font font) {
		std::string roundedMass = round_to_digits(mass, 2);
		std::string roundedvx = round_to_digits(velocity.x, 2);
		std::string roundedvy = round_to_digits(velocity.y, 2);
		std::string st = roundedMass + "kg" + " " + roundedvx + "ms^-1 x," + roundedvy + "ms^-1 y";
		sf::Text info(st, font);
		//std::cout << position.x / 1e-7 << std::endl;
		info.setPosition(std::truncf(position.x*1e-7), std::truncf(position.y*1e-7));
		info.setCharacterSize(15);
		info.setFillColor(sf::Color::Red);
		targetWindow.draw(info);
	}
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
	Tree<Particle> tree;
public:
	Simulation(float posrange, float masslower, float masshigher, int nbodies, float deltatime) :
		posRange(posrange), massLower(masslower), massHigher(masshigher), nBodies(nbodies), deltaTime(deltatime), bodies(new Body[nBodies]), tree(Tree<Particle>(bodies, nBodies)) {
		for (int i = 0; i < nBodies; i++) {
			bodies[i].position = vec2f::random(-posRange, posRange);
			bodies[i].mass = RandomFloat(massLower, massHigher);
		}
		tree.fit(bodies, nBodies);
	}
	void step() {
		tree.clear();
		tree.fill(bodies, nBodies);
		for (int i = 0; i < nBodies; ++i) {
			typedef Tree<Particle> QT;
			bodies[i].update(tree, deltaTime);
		}
	}
};