#include <iostream>
#include "Vector.h"
struct Body {
	vec2f position;
	Body() :
		position(vec2f()) {}
	Body(vec2f pos) :
		position(pos) {}
};
struct Node {
	float size;
	vec2f position;
	Node* parent;
	Node* children[4] = { nullptr, nullptr, nullptr, nullptr };
	Body* body;
public:
	Node() :
		size(0), position(vec2f()), parent(nullptr), body(nullptr) {}

	Node(const vec2f pos, const float s) :
		size(s), position(pos), parent(nullptr), body(nullptr) {}

	Node(Node* const p) :
		size(0), position(vec2f()), parent(p), body(nullptr) {}

	Node(Node* const p, const vec2f& pos, const float& s) :
		size(s), position(pos), parent(p), body(nullptr) {}

	~Node() {
		//std::cout << "deleted" << std::endl;
		if (hasChildren()) {
			for (Node*& child : children) {
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
		return body != nullptr;
	}
	bool contains(const vec2f& p) {
		//true if abs(x2-x1) < size && abs(y2 - y1) < size (ie within square)
		return (((position - p).abs()).less2d(size));
	}
	bool contains(Body* const& b) {
		//true if abs(x2-x1) < size && abs(y2 - y1) < size (ie within square)
		return (((position - b->position).abs()).less2d(size));
	}
	void subdivide() {
		//NW
		children[0] = new Node(this, position - vec2f(-size / 2, size / 2), size / 2);
		//NE
		children[1] = new Node(this, position - vec2f(size / 2, size / 2), size / 2);
		//SW
		children[2] = new Node(this, position - vec2f(-size / 2, -size / 2), size / 2);
		//SE
		children[3] = new Node(this, position - vec2f(size / 2, -size / 2), size / 2);
	}
	void insert(Body* const& b) {
		if (body == nullptr) {
			if (!hasChildren()) {
				body = b;
			}
			else {
				for (Node*& child : children) {
					if (child->contains(b))
						child->insert(b);
				}
			}
		}
		else {
			if (!hasChildren()) {
				subdivide();
			}
			for (Node* child : children) {
				if (child->contains(b))
					child->insert(b);
				if (child->contains(body))
					child->insert(body);
			}
			body = nullptr;
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

		for (Node* const& child : children) {
			n += child->countDescendants();
		}
		return n;
	}
	void print() {
		std::cout << "I am " << this << ". " << "I am a child of " << parent << ", I contain a Body* to " << body << ", and I am " << (hasChildren() ? "subdivided" : "not subdivided") << "." << std::endl;
	}
	void printchildren() {
		//if (children[0] != nullptr) {
		if (hasChildren()) {
			for (Node* child : children) {
				child->print();
			}
		}
	}
};
class BHtree {
public:
	Node* root;
public:
	BHtree() :
		root(nullptr) {}

	BHtree(Node* const& rt) :
		root(rt) {}

	template <size_t N>
	BHtree(Body* (&bodyptrs)[N]) :
		root(fit(bodyptrs)) {}

	void insert(Body* const& bodyptr) {
		root->insert(bodyptr);
	}
	void insert(const Body& body) {
		root->insert((Body*)&body);
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
	void fill(Body* (&bodyptrs)[N]) {
		root = fit(bodyptrs);
		for (Body* const& bodyptr : bodyptrs) {
			insert(bodyptr);
		}
	}
	template <size_t N>
	void fill(Body bodies[N]) {
		root = fit(bodies);
		for (const Body& body : bodies) {
			insert(body);
		}
	}
	template <size_t N>
	Node* fit(Body* (&bodyptrs)[N]) const {
		vec2f center = vec2f();
		for (Body* const& bodyptr : bodyptrs) {
			center += bodyptr->position;
		}
		center /= N;
		float magMax = 0.0f;
		for (Body* const& bodyptr : bodyptrs) {
			magMax = bodyptr->position.mag() > magMax ? bodyptr->position.mag() : magMax;
		}
		return new Node(center, magMax);
	}
	template <size_t N>
	Node* fit(Body bodies[N]) const {
		vec2f center = vec2f();
		for (Body const& body : bodies) {
			center += body.position;
		}
		center /= N;
		float magMax = 0.0f;
		for (Body const& body : bodies) {
			float tempMag = body.position.mag();
			magMax = tempMag > magMax ? tempMag : magMax;
		}
		return new Node(center, magMax);
	}

};
int main() {
	const unsigned int nBodies = 50000;
	Body bodies[nBodies];
	Body* bodyptrs[nBodies];
	for (int i = 0; i < nBodies; i++) {
		bodies[i].position = vec2f::random(-100.0f, 100.0f);
		bodyptrs[i] = &bodies[i];
	}
	
	BHtree tree;
	tree.fill(bodyptrs);
	std::cout << "# of Nodes: " << tree.countNodes() << std::endl;
	std::cout << sizeof(Body) * nBodies / 1000000.0f << "Mb of bodies" << std::endl;
	std::cout << sizeof(Node) * tree.countNodes() / 1000000.0f << "Mb of nodes" << std::endl;
	tree.clear();
	std::cin.get();
};