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

	vec2f getAccelerationBH (Tree::BHtree<Particle> tree) const {
		return recursiveBH(tree.root);
	}
	void getAccelerationNBODY(Body bodies[], int numBodies) const {

	}
	void update(Tree::BHtree<Particle> tree, vec2f(*accelerationFunction)(vec2f), float deltaTime) {
		
	}
private:
	inline const vec2f PPinteraction(Particle* const & me, Particle* const& other) const {
		return PPinteraction(me->mass, other->mass, other->position - me->position);
	}
	const inline vec2f PPinteraction(const float& mymass, const float& othermass, const vec2f& distanceVector) const {
		return distanceVector.norm()*(G*othermass/(distanceVector.mag2()*mymass));
	}
private:
	vec2f recursiveBH(Tree::Node<Particle>* node, vec2f pos) const{
		
		if (!node->hasChildren()) {//node is external
			if (node->particle == NULL) //external node is empty
				return vec2f();//return 0, 0
			else { //external node is not empty
				if (node->particle->position == pos) {
					return vec2f();
				}
				vec2f distanceVector = node->particle->position - pos;
				float myMass = this->mass;
				float otherMass = node->particle->mass;
				//float d2 = distanceVector.mag2();
				//float d = std::sqrt(d2);
				//std::cout << "PP:" << distanceVector.norm()*(G*otherMass / (distanceVector.mag2())) << "\n";
				return distanceVector.norm()*(G*otherMass / (distanceVector.mag2()));
			}
		}
		else {//node is internal
			vec2f acc;
			float s = node->size;
			vec2f d = node->position - pos;
			if ((node->size) / (d.mag()) < 0.5f) {
				vec2f COMpos;
				float COMmass;
				node->getCOM(COMpos, COMmass);
				//return PPinteraction(mass, COMmass, d);
				//std::cout << "norm: " << d.norm() << "\n";
				//std::cout << "mu: " << G * COMmass << "\n";
				//std::cout << "r^2: " << d.mag2() << "\n";
				//std::cout << "PCOM:" << d.norm()*(G*COMmass / (d.mag2())) << "\n";
				return d.norm()*(G*COMmass / (d.mag2()*this->mass));
			}
			else {
				for (Tree::Node<Particle>* const& child : node->children)
					acc += recursiveBH(child);
				return acc;
			}
		}
	}
};
class Simulation {
	float posRange;
	float massLower;
	float massHigher;
	unsigned int nBodies;
	float deltaTime;
	Body* bodies;
	Particle* bodyptrs[];
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
		for (int i = 0; i < nBodies; i++) {
			bodies[i].update(tree, Body::getAccelerationBH, deltaTime);
		}
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
	//Body* bodyptrss = (Body*)bodyptrs;
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < nBodies; j++) {
			bodies[j].update(bodies[j].getAccelerationBH());
		}
	}
	Tree::BHtree<Particle> tree;
	tree.fill(bodyptrs);
	std::cout << "# of Nodes: " << tree.countNodes() << std::endl;
	std::cout << sizeof(Particle) * nBodies / 1000000.0f << "Mb of particles" << std::endl;
	std::cout << sizeof(Tree::Node<Particle>) * tree.countNodes() / 1000000.0f << "Mb of nodes" << std::endl;
	std::cout << sizeof(Tree::Node<Particle>) << std::endl;

	


	tree.clear();
	
	
	std::cout << "Tree cleared" << std::endl;
	//unsigned concurentThreadsSupported = std::thread::hardware_concurrency();
	//std::cout << concurentThreadsSupported << std::endl;
	std::cin.get();
};