#pragma once
#include "Vector.h"
#include <vector>
namespace Tree {
	template <typename Particle>
	struct Node {
		float size;
		vec2f position;
		Node<Particle>* parent;
		Node<Particle>* children[4] = { nullptr, nullptr, nullptr, nullptr };
		Particle* particle;
	public:
		Node() :
			size(0), position(vec2f()), parent(nullptr), particle(nullptr) {}

		Node(const vec2f pos, const float s) :
			size(s), position(pos), parent(nullptr), particle(nullptr) {}

		Node(Node<Particle>* const p) :
			size(0), position(vec2f()), parent(p), particle(nullptr) {}

		Node(Node<Particle>* const p, const vec2f& pos, const float& s) :
			size(s), position(pos), parent(p), particle(nullptr) {}

		~Node() {
			//std::cout << "deleted" << std::endl;
			if (hasChildren()) {
				for (Node<Particle>*& child : children) {
					delete child;
				}
			}
		}
	public:
		inline bool hasChildren() {
			return children[0] != nullptr;
		}
		inline bool hasParent() {
			return parent != nullptr;
		}
		inline bool isLeaf() {
			return particle != nullptr;
		}
		bool contains(const vec2f& p) {
			//true if abs(x2-x1) < size && abs(y2 - y1) < size (ie within square)
			return (((position - p).abs()).less2d(size));
		}
		bool contains(Particle* const& b) {
			//true if abs(x2-x1) < size && abs(y2 - y1) < size (ie within square)
			return (((position - b->position).abs()).less2d(size));
		}
		void subdivide() {
			//NW
			children[0] = new Node<Particle>(this, position - vec2f(-size / 2, size / 2), size / 2);
			//NE
			children[1] = new Node<Particle>(this, position - vec2f(size / 2, size / 2), size / 2);
			//SW
			children[2] = new Node<Particle>(this, position - vec2f(-size / 2, -size / 2), size / 2);
			//SE
			children[3] = new Node<Particle>(this, position - vec2f(size / 2, -size / 2), size / 2);
		}
		void insert(Particle* const& b) {
			if (!isLeaf()) {
				if (!hasChildren()) {
					particle = b;
				}
				else {
					for (Node<Particle>*& child : children) {
						if (child->contains(b))
							child->insert(b);
					}
				}
			}
			else {
				if (!hasChildren()) {
					subdivide();
				}
				for (Node<Particle>* child : children) {
					if (child->contains(b))
						child->insert(b);
					if (child->contains(particle))
						child->insert(particle);
				}
				particle = nullptr;
			}
		}
		int countDescendants() {
			int n = 0;
			if (!hasChildren()) {
				if (hasParent())
					return 1;
				else
					return 0;
			}
			else if (hasParent())
				n++;
			for (Node<Particle>* const& child : children)
				n += child->countDescendants();
			return n;
		}
		void print() {
			std::cout << "I am " << this << ". " << "I am a child of " << parent << ", I contain a particle* to " << particle << ", and I am " << (hasChildren() ? "subdivided" : "not subdivided") << "." << std::endl;
		}
		void printchildren() {
			//if (children[0] != nullptr) {
			if (hasChildren()) {
				for (Node<Particle>* child : children) {
					child->print();
				}
			}
		}
	public:
		void getCOM(vec2f& outposition, float& outmass) {
			if (hasChildren()) {
				for (Node* const& child : children)
					child->getCOM(outposition, outmass);
			}
			else {
				outposition = particle->position;
				outmass = particle->mass;
			}
		}

	};
	template <typename Particle>
	class BHtree {
	public:
		Node<Particle>* root;
	public:
		BHtree() :
			root(nullptr) {}

		BHtree(Node<Particle>* const& rt) :
			root(rt) {}

		template <size_t N>
		BHtree(Particle* (&particleptrs)[N]) :
			root(fit(particleptrs)) {}

		void insert(Particle* const& particleptr) {
			root->insert(particleptr);
		}
		void insert(const Particle& particle) {
			root->insert((Particle*)&particle);
		}
		int countNodes() {
			return root->countDescendants() + 1;
		}
	public:
		void clear() {
			delete root; //deleting a node deletes all of its children recursively.
			root = nullptr;
		}
		template <size_t N>
		void fill(Particle* (&particleptrs)[N]) {
			root = fit(particleptrs);
			for (Particle* const& particleptr : particleptrs) {
				insert(particleptr);
			}
		}
		template <size_t N>
		void fill(Particle particles[N]) {
			root = fit(particles);
			for (const Particle& particle : particles) {
				insert(particle);
			}
		}
		void fill(std::vector<Particle*> particleptrs) {
			root = fit(particleptrs);
			for (Particle* const& particleptr : particleptrs) {
				insert(particleptr);
			}
		}
		template <size_t N>
		Node<Particle>* fit(Particle* (&particleptrs)[N]) const {
			vec2f center = vec2f();
			for (Particle* const& particleptr : particleptrs) {
				center += particleptr->position;
			}
			center /= N;
			float magMax = 0.0f;
			for (Particle* const& particleptr : particleptrs) {
				magMax = particleptr->position.mag() > magMax ? particleptr->position.mag() : magMax;
			}
			return new Node<Particle>(center, magMax);
		}
		template <size_t N>
		Node<Particle>* fit(std::vector<Particle*> particleptrs[N]) const {
			vec2f center = vec2f();
			for (Particle* const& particleptr : particleptrs) {
				center += particleptr->position;
			}
			center /= N;
			float magMax = 0.0f;
			for (Particle* const& particleptr : particleptrs) {
				magMax = particleptr->position.mag() > magMax ? particleptr->position.mag() : magMax;
			}
			return new Node<Particle>(center, magMax);
		}
		template <size_t N>
		Node<Particle>* fit(Particle particles[N]) const {
			vec2f center = vec2f();
			for (Particle const& particle : particles) {
				center += particle.position;
			}
			center /= N;
			float magMax = 0.0f;
			for (Particle const& particle : particles) {
				float tempMag = particle.position.mag();
				magMax = tempMag > magMax ? tempMag : magMax;
			}
			return new Node<Particle>(center, magMax);
		}
	};
}
