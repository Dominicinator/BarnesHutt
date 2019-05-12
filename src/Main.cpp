#include <iostream>
#include "Vector.h"
#include "BarnesHuttTree.h"
#include <thread>
#include <vector>
const float G = 6.67408E-11f;
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

	vec2f getAccelerationBH (Tree::BHtree<Particle> tree) const {
		return recursiveBH(tree.root);
	}
	void getAccelerationNBODY(Body bodies[], int numBodies) const {

	}
	void update() {

	}
private:
	inline const vec2f PPinteraction(Particle* const & me, Particle* const& other) const {
		return PPinteraction(me->mass, other->mass, other->position - me->position);
	}
	const inline vec2f PPinteraction(const float& mymass, const float& othermass, const vec2f& distanceVector) const {
		return distanceVector.norm()*(G*othermass/(distanceVector.mag2()*mymass));
	}
private:
	vec2f recursiveBH(Tree::Node<Particle>* node) const{
		
		if (!node->hasChildren()) {//node is external
			if (node->particle) //external node is empty
				return vec2f();//return 0, 0
			else { //external node is not empty
				vec2f distanceVector = node->particle->position - this->position;
				float myMass = this->mass;
				float otherMass = node->particle->mass;
				//float d2 = distanceVector.mag2();
				//float d = std::sqrt(d2);
				return distanceVector.norm()*(G*otherMass / (distanceVector.mag2()*myMass));
			}
		}
		else {//node is internal
			vec2f acc;
			float s = node->size;
			vec2f d = node->position - this->position;
			if ((node->size) / (d.mag()) < 0.5f) {
				vec2f COMpos;
				float COMmass;
				node->getCOM(COMpos, COMmass);
				//return PPinteraction(mass, COMmass, d);
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
int main() {
	namespace Q = Tree;
	const unsigned int nBodies = 4;
	Body* bodies = new Body[nBodies];
	//Body** bodyptrs = new Body*[nBodies];
	Particle* bodyptrs[nBodies];
	for (int i = 0; i < nBodies; i++) {
		bodies[i].position = vec2f::random(-100.0f, 100.0f);
		bodyptrs[i] = &bodies[i];
	}
	//Body* bodyptrss = (Body*)bodyptrs;
	
	Q::BHtree<Particle> tree;
	tree.fill(bodyptrs);
	std::cout << "# of Nodes: " << tree.countNodes() << std::endl;
	std::cout << sizeof(Particle) * nBodies / 1000000.0f << "Mb of particles" << std::endl;
	std::cout << sizeof(Q::Node<Particle>) * tree.countNodes() / 1000000.0f << "Mb of nodes" << std::endl;
	std::cout << sizeof(Q::Node<Particle>) << std::endl;

	//std::cin.get();
	vec2f acc = bodies[0].getAccelerationBH(tree);
	std::cout << acc.x << ", " << acc.y << std::endl;


	tree.clear();
	
	
	std::cout << "Tree cleared" << std::endl;
	unsigned concurentThreadsSupported = std::thread::hardware_concurrency();
	std::cout << concurentThreadsSupported << std::endl;
	std::cin.get();
};