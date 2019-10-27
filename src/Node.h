#pragma once
#include "Vector.h"
#include "SFML/Graphics.hpp"
template<typename DataType>
class Node
{
public:
	Node<DataType>* parent;
	Node<DataType>* children[4] = { nullptr, nullptr, nullptr, nullptr };
	DataType* data = nullptr;
	float size;
	vec2f position;
	bool empty = true;
	//Constructors and Destructors
	//Empty Constructor
	Node() :
		parent(nullptr), position(vec2f()), size(0.0f) {}
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
		return (position - data->position).abs() < size/2;
	}
	void subdivide()
	{
		std::cout << "subdivided" << std::endl;
		//NW
		children[0] = new Node<DataType>(this, position - vec2f(-size / 4, size / 4), size / 2);
		//NE
		children[1] = new Node<DataType>(this, position - vec2f(size / 4, size / 4), size / 2);
		//SW
		children[2] = new Node<DataType>(this, position - vec2f(-size / 4, -size / 4), size / 2);
		//SE
		children[3] = new Node<DataType>(this, position - vec2f(size / 4, -size / 4), size / 2);
	}
	void insert(void* const& b) {

	}
	void insert(DataType* const& b)
	{
		std::cout << "insert" << std::endl;
		if (!contains(b)) {
			return;
		}
		if (empty) {
			if (!hasChildren()) {
				data = b;
				empty = false;
			}
			else {
				for (Node<DataType>*& child : children) {
					if (child->contains(b))
						child->insert(b);
				}
				empty = true;
			}
		}
		else {
			if (!hasChildren()) {
				subdivide();
			}
			for (Node<DataType>* child : children) {
				if (child->contains(b)) {
					std::cout << child << " contains " << b << std::endl;
					child->insert(b);
				}
				if (child->contains(data))
					std::cout << child << " contains " << data << std::endl;
					child->insert(data);
			}
			data = nullptr;
			empty = true;
		}
	}
	void debugprint(std::string start) {
		if (!parent) {
			std::cout << "Root";
			if (!empty) {
				std::cout << " " << data << std::endl;
			}
			else {
				std::cout << std::endl;
			}
		}
		else {
			if (empty) {
				std::cout << start + "Internal" << std::endl;
			}
			else {
				std::cout << start + "Leaf " << data << std::endl;
			}
		}
		if (hasChildren())
			for (auto child : children) {
				child->debugprint(start + "-");
			}
		
	}
	void draw(sf::RenderWindow& targetWindow)
	{
		sf::RectangleShape rect(sf::Vector2f(size, size));
		rect.setOrigin(size / 2, size / 2);
		rect.setPosition(position.x, position.y);
		//rect.setPosition(position.x - size / 2, position.y - size / 2);
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Transparent);
		rect.setOutlineThickness(1.0f);
		if (!empty) {
			rect.setOutlineColor(sf::Color::Blue);
			rect.setOutlineThickness(2.0f);
		}
		
		targetWindow.draw(rect);
		if (hasChildren())
			for (auto child : children) {
				child->draw(targetWindow);
			}
	}
};

