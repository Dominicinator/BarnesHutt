#pragma once
#include "Vector.h"
#include <thread>
#include <vector>
#include "Tree.h"

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
	float radius = 1.0f;
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
	void debug() {

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
		tree.fill(bodies, nBodies);
		for (int i = 0; i < nBodies; ++i) {
			typedef Tree<Particle> QT;
			bodies[i].update(tree, deltaTime);
		}
		tree.clear();
	}
};