#include "Node.h"

template <typename NodeData>
Node<NodeData>::Node() :
	size(0), position(vec2f()), parent(nullptr), data(nullptr) {}

template <typename NodeData>
Node<NodeData>::Node(const vec2f& pos, const float& s) :
	size(s), position(pos), parent(nullptr), data(nullptr) {}

template <typename NodeData>
Node<NodeData>::Node(Node<NodeData>* const p) :
	size(0), position(vec2f()), parent(p), data(nullptr) {}

template <typename NodeData>
Node<NodeData>::Node(Node<NodeData>* const p, const vec2f& pos, const float& s) :
	size(s), position(pos), parent(p), data(nullptr) {}

template <typename NodeData>
Node<NodeData>::~Node()
{
	if (hasChildren()) {
		for (Node<NodeData>*& child : children) {
			delete child;
		}
	}
}
template<typename NodeData>
inline bool Node<NodeData>::contains(NodeData* const & d)
{
	//True if each component of abs distance is less than size
	return (position - d->position).abs() < size;
}
template<typename NodeData>
inline bool Node<NodeData>::isEmpty()
{
	return data == nullptr;
}
template<typename NodeData>
inline bool Node<NodeData>::hasChildren()
{
	return children[0] != nullptr;
}
template<typename NodeData>
void Node<NodeData>::subdivide()
{
	//NW
	children[0] = new Node<NodeData>(this, position - vec2f(-size / 2, size / 2), size / 2);
	//NE
	children[1] = new Node<NodeData>(this, position - vec2f(size / 2, size / 2), size / 2);
	//SW
	children[2] = new Node<NodeData>(this, position - vec2f(-size / 2, -size / 2), size / 2);
	//SE
	children[3] = new Node<NodeData>(this, position - vec2f(size / 2, -size / 2), size / 2);
}

template<typename NodeData>
void Node<NodeData>::insert(NodeData * const & d)
{
	if (isEmpty()) {
		if (!hasChildren()) {
			data = d;
		}
		else {
			for (Node<NodeData>*& child : children) {
				if (child->contains(d))
					child->insert(d);
			}
		}
	}
	else {
		if (!hasChildren()) {
			subdivide();
		}
		for (Node<NodeData>* child : children) {
			if (child->contains(d))
				child->insert(d);
			if (child->contains(data))
				child->insert(data);
		}
		data = nullptr;
	}
}

template<typename NodeData>
void Node<NodeData>::draw(sf::RenderWindow & window)
{
	sf::RectangleShape rect(sf::Vector2f(size, size));
	rect.setPosition(0.0f, 0.0f);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Green);
	rect.setOutlineThickness(1.0f);
	window.draw(rect);
}

