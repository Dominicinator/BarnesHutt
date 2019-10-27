#pragma once
#include "Vector.h"
#include "SFML/Graphics.hpp"
template<typename DataType>
class Node
{
public:
	Node<DataType>* parent;
	Node<DataType>* children[4] = { nullptr, nullptr, nullptr, nullptr };
	DataType* data;
	float size;
	vec2f position;
	//Constructors and Destructors
	//Empty Constructor
	Node() :
		parent(nullptr) {}
	//Parent Constructor
	Node(Node<DataType>* const & parent) :
		parent(parent), position(vec2f()), size(0.0f) {}
	//Position and Size Constructor
	Node(const vec2f & position, const float & size) :
		parent(nullptr), position(position), size(size) {}
	//Parent, position, and size Constructor
	Node(Node<DataType>* const & parent, const vec2f & position, const float & size) :
		parent(parent), position(position), size(size) {}
	//Recursively delete node and all of its children
	virtual ~Node() 
	{
		if (hasChildren())
			for (auto child : children) {
				delete child;
			}
	}
	inline bool hasChildren()
	{
		return children[0] != nullptr;
	}
	inline bool contains(DataType* const& data)
	{
		return (position - data.position).abs() < size;
	}
	void subdivide()
	{

	}
	void insert(DataType* const& b)
	{
	}
	void draw(sf::RenderWindow& targetWindow)
	{
		sf::RectangleShape rect(sf::Vector2f(size, size));
		rect.setPosition(position.x - size / 2, position.y - size / 2);
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Green);
		rect.setOutlineThickness(2.0f);
		targetWindow.draw(rect);
		if (hasChildren())
			for (auto child : children) {
				child->draw(targetWindow);
			}
	}
};

