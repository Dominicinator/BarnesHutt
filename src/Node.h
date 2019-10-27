#pragma once
#include "Vector.h"
#include "SFML/Graphics.hpp"
template <typename NodeData>
struct Node
{
public:
	//Variables
	int dimension = 2;
	float size;
	vec2f position;
	Node<NodeData>* parent;
	Node<NodeData>* children[4] = { nullptr, nullptr, nullptr, nullptr };
	NodeData* data;
	/*Constructors and Destructors*/
	//Empty Constructor
	Node();
	//Position and Size constructor
	Node(const vec2f& pos, const float& s);
	//Parent constructor
	Node(Node<NodeData>* const p);
	//Position, size, and parent constructor
	Node(Node<NodeData>* const p, const vec2f& pos, const float& s);
	//Destructor
	virtual ~Node();
	/*Functions*/
	//Utility
	//Check if node contains data
	inline bool contains(NodeData* const & d);
	//Check if node has children
	inline bool hasChildren();
	//check if node is empty
	inline bool isEmpty();
	//Implimentation
	void subdivide();
	void insert(NodeData* const & d);
	//Debug
	//Recursively draw node and its children
	void draw(sf::RenderWindow& window);
	
};

