#include <iostream>
#include "Vector.h"
#include "BarnesHuttTree.h"
#include <thread>
#include <vector>

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
	void update(Tree::BHtree<Particle> tree, const vec2f(*accelerationFunction)(const vec2f&), float deltaTime) {
		return;
	}
};
//template <int nBodies>
class Simulation {
	float posRange;
	float massLower;
	float massHigher;
	unsigned int nBodies;
	float deltaTime;
	Body* bodies;
	Tree::BHtree<Particle> tree;
	Simulation(float posrange, float masslower, float masshigher, int nbodies, float deltatime) : posRange(posrange), massLower(masslower), massHigher(masshigher), nBodies(nbodies), deltaTime(deltatime) {
		bodies = new Body[nBodies];
		for (int i = 0; i < nBodies; i++) {
			bodies[i].position = vec2f::random(-posRange, posRange);
			bodies[i].mass = RandomFloat(massLower, massHigher);
		}
	}
	void step() {
		tree.fill(bodies, nBodies);
		for (int i = 0; i < nBodies; i++) {
			std::cout << tree.getAcceleration << std::endl;
			bodies[i].update(tree, tree.getAcceleration, deltaTime);
		}
		tree.clear();
	}
};
int main() {
	const float posRange = 1E9;
	const float massLower = 1E23f;
	const float massHigher = 1E26f;
	const unsigned int nBodies = 50;
	Body* bodies = new Body[nBodies];
	for (int i = 0; i < nBodies; i++) {
		bodies[i].position = vec2f::random(-posRange, posRange);
		bodies[i].mass = RandomFloat(massLower, massHigher);
	}
	
	Tree::BHtree<Particle> tree;
	tree.fill(bodies, nBodies);
	std::cout << "# of Nodes: " << tree.countNodes() << std::endl;
	std::cout << sizeof(Particle) * nBodies / 1000000.0f << "Mb of particles" << std::endl;
	std::cout << tree.getSize() / 1000000.0f << "Mb of nodes" << std::endl;
	std::cout << sizeof(Tree::Node<Particle>) << std::endl;

	


	
	
	
	std::cout << "Tree cleared" << std::endl;
	std::cin.get();
};