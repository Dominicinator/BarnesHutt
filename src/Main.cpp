#include <iostream>
#include "Vector.h"
#include "BarnesHuttTree.h"
#include <thread>
#include <vector>
const float G = 6.67408E-11f;
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
	static enum calculationMethod {
		BARNESHUTT, NBODY
	};
	void update(Tree::BHtree<Particle> tree, vec2f(*accelerationFunction)(vec2f), float deltaTime) {
		
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
	Particle** bodyptrs;
	Tree::BHtree<Particle> tree;
	Simulation(float posrange, float masslower, float masshigher, int nbodies, float deltatime) : posRange(posrange), massLower(masslower), massHigher(masshigher), nBodies(nbodies), deltaTime(deltatime) {
		bodies = new Body[nBodies];
		for (int i = 0; i < nBodies; i++) {
			bodies[i].position = vec2f::random(-posRange, posRange);
			bodies[i].mass = RandomFloat(massLower, massHigher);
			bodyptrs[i] = &bodies[i];
		}
	}
	Simulation() : posRange(100.0f), massLower(10.0f), massHigher(10.0f), nBodies(5) {
		bodies = new Body[nBodies];
		for (int i = 0; i < nBodies; i++) {
			bodies[i].position = vec2f::random(-posRange, posRange);
			bodies[i].mass = RandomFloat(massLower, massHigher);
			bodyptrs[i] = &bodies[i];
		}
	}
	void step() {
		tree.fill(bodyptrs);
		for (int i = 0; i < nBodies; i++) {
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
	//Body** bodyptrs = new Body*[nBodies];
	Particle* bodyptrs[nBodies];
	for (int i = 0; i < nBodies; i++) {
		bodies[i].position = vec2f::random(-posRange, posRange);
		bodies[i].mass = RandomFloat(massLower, massHigher);
		bodyptrs[i] = &bodies[i];
	}
	
	Tree::BHtree<Particle> tree;
	tree.fill(bodyptrs);
	std::cout << "# of Nodes: " << tree.countNodes() << std::endl;
	std::cout << sizeof(Particle) * nBodies / 1000000.0f << "Mb of particles" << std::endl;
	std::cout << tree.getSize() / 1000000.0f << "Mb of nodes" << std::endl;
	std::cout << sizeof(Tree::Node<Particle>) << std::endl;

	


	
	
	
	std::cout << "Tree cleared" << std::endl;
	std::cin.get();
};