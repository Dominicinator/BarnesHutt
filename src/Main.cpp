#include <iostream>
//#include "Simulation.h"
#include "Node.h"
struct Particle {
	float position = 0.0f;
};
	
int main() {
	Node<Particle> node(vec2f(0.0f, 0.0f), 100.0f);
	sf::RenderWindow window(sf::VideoMode(800, 800), "Title");
	sf::Event event;
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 800.0f));
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);
		window.setView(view);
		node.draw(window);
		window.display();
	}
	return 0;
}
/*
inline float map(const float& a, const float& b, const float& c, const float& d, const float& x) {
	return (x - a) * (d - c) / (d - a) + c;
}

int main() {
	Simulation sim(1E9f, 1E20, 1E22, 2, 1000.0f);
	std::cout << sim.bodies[0].position << std::endl;
	sim.step();
	std::cout << sim.bodies[0].position << std::endl;
	sim.step();
	//std::cin.get();
	float windowWidth = 800;
	float windowHeight = 800;
	sf::RenderWindow window(sf::VideoMode(800, 800), "Title");

	sf::Event event;

	//sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 800.0f));

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		sim.step();
		window.clear(sf::Color::Black);
		for (int i = 0; i < sim.nBodies; ++i) {
			sf::Vector2f windowPos = sf::Vector2f(sim.bodies[i].position.x, sim.bodies[i].position.y);
			float x = map(-sim.posRange, sim.posRange, 0.0f, windowWidth, sim.bodies[i].position.x);
			float y = map(-sim.posRange, sim.posRange, 0.0f, windowWidth, sim.bodies[i].position.y);
			sf::CircleShape planetShape(100.0f);
			//planetShape.setPosition(0.0f, 0.0f);
			//planetShape.setPosition(x, y);
			if (i == 0)
				std::cout << x << std::endl;
			//std::cout << y << std::endl;
			planetShape.setFillColor(sf::Color(0, 255, 0));
			window.draw(planetShape);
		}
		window.display();
	}
	return 0;
};
*/
