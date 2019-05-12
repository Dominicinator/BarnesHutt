#pragma once
#include "Vector.h"
#include <vector>
const float G = 6.67408E-11f;
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
		inline bool isEmptyExternal() {
			return (!hasChildren() && !hasParticle());
		}
		inline bool hasChildren() {
			return children[0] != nullptr;
		}
		inline bool hasParent() {
			return parent != nullptr;
		}
		inline bool hasParticle() {
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
			if (!hasParticle()) {
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
			else if (hasParticle()){
				outposition = particle->position;
				outmass = particle->mass;
			}
		}

	};
	template <typename Particle>
	class BHtree {
	public:
		Node<Particle>* root;
		float rootSize;
		vec2f rootPos;
	public:
		BHtree() :
			root(nullptr) {}

		BHtree(Node<Particle>* const& rt) :
			root(rt) {}
		BHtree(Particle* const& particles, int nParticles) :
			root(new Node<Particle>) {
			fit(particles, nParticles);
		}
		void insert(Particle* const& particleptr) {
			root->insert(particleptr);
		}
		void insert(const Particle& particle) {
			root->insert(&particle);
		}
		
	public:
		//Util
		int countNodes() {
			return root->countDescendants() + 1;
		}
		float getSize() {
			return sizeof(Particle)*countNodes();
		}
	public:
		void clear() {
			for (auto const& child : root->children) {
				delete child; //deleting a node deletes all of its children recursively.
				child = nullptr;
			}
		}
		void fill(Particle* const& particles, int nParticles) {
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
			vec2f center;
			float magMax;
			for (int i = 0; i < nParticles; i++) {
				center += particles[i].position;
			}
			center /= nParticles;
			for (int i = 0; i < nParticles; i++) {
				magMax = particles[i].position.mag() > magMax ? particles[i].position.mag() : magMax;
			}
			rootPos = center;
			rootSize = magMax;
			root->position = center;
			root->size = magMax;
		}
		
	public:
		const vec2f getAcceleration(const vec2f& pos) const {
			return _getAcceleration(root, pos);
		}
	private:
		const vec2f _getAcceleration(Tree::Node<Particle>* const& node, const vec2f& pos) const {

			if (!node->hasChildren()) {//node is external
				if (node->particle == NULL) //external node is empty
					return vec2f();//return 0, 0
				else { //external node is not empty
					if (node->particle->position == pos) {
						return vec2f();
					}
					vec2f distanceVector = node->particle->position - pos;
					return distanceVector.norm()*(G*node->particle->mass / (distanceVector.mag2()));
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
					return d.norm()*(G*COMmass / (d.mag2()));
				}
				else {
					for (Tree::Node<Particle>* const& child : node->children)
						acc += _getAcceleration(child);
					return acc;
				}
			}
		}
	};
}