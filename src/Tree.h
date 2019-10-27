#pragma once
#include "Node.h"
template<typename Node, typename Data>
class Tree {
public:
	Node root;
	Tree<Node>() :
		root(Node()) {}
	void fill(Data* & data) {

	}
};