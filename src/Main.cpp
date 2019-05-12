#include <iostream>
#include "Vector.h"
#include "BarnesHuttTree.h"
struct Body {
	vec2f position;
	Body() :
		position(vec2f()) {}
	Body(vec2f pos) :
		position(pos) {}
};
int main() {
	namespace Q = Tree;
	const unsigned int nBodies = 50000;
	Body bodies[nBodies];
	Body* bodyptrs[nBodies];
	for (int i = 0; i < nBodies; i++) {
		bodies[i].position = vec2f::random(-100.0f, 100.0f);
		bodyptrs[i] = &bodies[i];
	}
	
	Q::BHtree<Body> tree;
	tree.fill(bodyptrs);
	std::cout << "# of Nodes: " << tree.countNodes() << std::endl;
	std::cout << sizeof(Body) * nBodies / 1000000.0f << "Mb of bodies" << std::endl;
	std::cout << sizeof(Q::Node<Body>) * tree.countNodes() / 1000000.0f << "Mb of nodes" << std::endl;
	std::cout << sizeof(Q::Node<Body>) << std::endl;
	tree.clear();
	std::cout << "Tree cleared" << std::endl;
	std::cin.get();
};