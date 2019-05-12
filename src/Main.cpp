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
	//template<typename T>
	void update(Tree::BHtree<Particle> tree, const vec2f(Tree::BHtree<Particle>::*accelerationFunction)(const vec2f&) const, float deltaTime) {
		return;
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
	Tree::BHtree<Particle> tree;
public:
	Simulation(float posrange, float masslower, float masshigher, int nbodies, float deltatime) :
		posRange(posrange), massLower(masslower), massHigher(masshigher), nBodies(nbodies), deltaTime(deltatime), bodies(new Body[nBodies]), tree(Tree::BHtree<Particle>(bodies, nBodies)) {
		//
		;
		for (int i = 0; i < nBodies; i++) {
			bodies[i].position = vec2f::random(-posRange, posRange);
			bodies[i].mass = RandomFloat(massLower, massHigher);
		}
		tree.fit(bodies, nBodies);
	}
	void step() {
		tree.fill(bodies, nBodies);
		for (int i = 0; i < nBodies; i++) {
			typedef Tree::BHtree<Particle> QT;
			//auto accFunc = &Tree::BHtree<Particle>::getAcceleration;
			//auto accFunc = tree.getAcceleration;
			const vec2f (QT::*accFunc)(const vec2f&) const = &QT::getAcceleration; // get a pointer to tree.getAcceleration
			//auto accFunc = &QT::getAcceleration;
			//std::cout << accFunc << std::endl;
			bodies[i].update(tree, accFunc, deltaTime);
		}
		tree.clear();
	}
};
int main() {
	//const float posRange = 1E9;
	//const float massLower = 1E23f;
	//const float massHigher = 1E26f;
	//const unsigned int nBodies = 50;
	//Body* bodies = new Body[nBodies];
	//for (int i = 0; i < nBodies; i++) {
	//	bodies[i].position = vec2f::random(-posRange, posRange);
	//	bodies[i].mass = RandomFloat(massLower, massHigher);
	//}
	//
	////Tree::BHtree<Particle> tree;
	////tree.fill(bodies, nBodies);
	//Tree::BHtree<Particle> tree(bodies, nBodies);
	//tree.fill(bodies, nBodies);
	//tree.clear();
	//tree.fill(bodies, nBodies);
	//std::cout << "# of Nodes: " << tree.countNodes() << std::endl;
	//std::cout << sizeof(Particle) * nBodies / 1000000.0f << "Mb of particles" << std::endl;
	//std::cout << tree.getSize() / 1000000.0f << "Mb of nodes" << std::endl;
	//std::cout << sizeof(Tree::Node<Particle>) << std::endl;
	Simulation sim(1E9f, 1E20, 1E22, 50, 1);
	std::cout << sim.bodies[0].position << std::endl;
	sim.step();
	std::cout << sim.bodies[0].position << std::endl;
	std::cin.get();
};