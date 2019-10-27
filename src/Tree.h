#pragma once
#include "Node.h"
const float G = 6.67408E-11f;
template<typename Particle>
class Tree {
public:
	Node<Particle>* root;
	float rootSize;
	vec2f rootPos;
public:
	Tree() :
		root(nullptr) {}

	Tree(Node<Particle>* const& rt) :
		root(rt) {}
	Tree(Particle* const& particles, int nParticles) :
		root(new Node<Particle>) {
		fit(particles, nParticles);
	}
	void insert(Particle* const& particleptr) {
		root->insert(particleptr);
	}
	void insert(Particle& particle) {
		root->insert(&particle);
	}
private:
	void initRoot() {
		root = new Node<Particle>;
	}
public:
	//Util
	int countNodes() {
		return root->countDescendants() + 1;
	}
	unsigned int getSize() {
		return sizeof(Particle)*countNodes();
	}
	void draw(float scale, sf::RenderWindow& targetWindow) {
		root->draw(scale, targetWindow);
	}
	void debugprint() {
		if (root)
			root->debugprint("");
	}
public:
	void clear() {
		for (auto& child : root->children) {
			delete child; //deleting a node deletes all of its children recursively.
			child = nullptr;
			root->data = nullptr;
			root->empty = true;
		}
	}
	void fill(Particle* const& particles, int nParticles) {
		if (root == nullptr)
			initRoot();
		fit(particles, nParticles);
		for (int i = 0; i < nParticles; i++) {
			insert(particles[i]);
		}
	}
	void fill_nofit(Particle* const& bodies, int nParticles) {
		for (int i = 0; i < nParticles; i++) {
			insert(bodies[i]);
		}
	}
	void fit(Particle* const& particles, int nParticles) {
		//for (int i = 0; i < nParticles; ++i) {
			//particles[i].print();
		//}
		vec2f center = vec2f();
		float magMax = 0;
		for (int i = 0; i < nParticles; i++) {
			center += particles[i].position;
		}
		center /= (const float&)nParticles;
		for (int i = 0; i < nParticles; i++) {
			float mag = (particles[i].position - center).mag();
			magMax =  mag > magMax ? mag : magMax;
		}
		//std::cout << "Center:" << center << std::endl;
		//std::cout << "Size: " << magMax * 2 << std::endl;
		root->position = center;
		root->size = magMax*2;
	}
	void fill(std::vector<Particle> particles) {
		if (root == nullptr)
			initRoot();
		fit(particles);
		for (auto particle : particles) {
			insert(particle);
		}
	}
	void fit(std::vector<Particle> particles) {
		vec2f center;
		float magMax = 0.0f;
		for (auto particle : particles) {
			center += particle.position;
		}
		center /= particles.size();
		//center = vec2f(0.0f, 0.0f);
		for (auto particle : particles) {
			magMax = (particle.position-center).mag() > magMax ? (particle.position-center).mag() : magMax;
		}
		root->position = center;
		root->size = magMax*2;
	}

public:
	const vec2f getAcceleration(const vec2f& pos) const {
		return _getAcceleration(root, pos);
	}
private:
	const vec2f _getAcceleration(Node<Particle>* const& node, const vec2f& pos) const {

		if (!node->hasChildren()) {//node is external
			if (node->data == NULL) //external node is empty
				return vec2f();//return 0, 0
			else { //external node is not empty
				if (node->data->position == pos) {
					return vec2f();
				}
				vec2f distanceVector = node->data->position - pos;
				return distanceVector.norm()*(G*node->data->mass / (distanceVector.mag2()));
			}
		}
		else {//node is internal
			vec2f acc;
			float s = node->size;
			vec2f d = node->position - pos;
			if ((node->size) / (d.mag()) < 0.5f) {
				vec2f COMpos = vec2f();
				float COMmass = 0.0f;
				node->getCOM(COMpos, COMmass);
				d = COMpos - pos;
				return d.norm()*(G*COMmass / (d.mag2()));
			}
			else {
				for (Node<Particle>* const& child : node->children)
					acc += _getAcceleration(child, pos);
				return acc;
			}
		}
	}
};