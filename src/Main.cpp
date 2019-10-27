#include <iostream>
//#include "Simulation.h"
#include "Tree.h"
struct Particle {
	vec2f position;
	vec2f velocity;
	float mass;
	float radius = 5.0f;
	Particle() :
		position(vec2f()) {}
	Particle(vec2f position) :
		position(position) {}
	void draw(sf::RenderWindow & targetWindow) {
		sf::CircleShape circle(radius);
		//std::cout << "initial position: " << circle.getPosition().x << "," << circle.getPosition().y << std::endl;
		circle.setPosition(position.x- radius, position.y- radius);
		circle.setFillColor(sf::Color::White);
		targetWindow.draw(circle);
	}
};
	
int main() {
	sf::Font font;
	font.loadFromFile("G:/dev/BarnesHutt/BarnesHutt/src/arial_narrow_7.ttf");
	int particleCount = 0;
	Particle particles[1000];
	particleCount = 1;
	particles[0] = Particle();

	Tree<Particle> tree = Tree<Particle>();
	tree.fill(particles, particleCount);
	//Node<Particle> node(vec2f(0.0f, 0.0f), 100.0f);
	float windowWidth = 800.0f;
	float windowHeight = 800.0f;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Title");
	sf::Event event;
	sf::Vector2f cameraPosition(0.0f, 0.0f);
	sf::View view(cameraPosition, sf::Vector2f(windowWidth, windowHeight));
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
				int worldMouseX = sf::Mouse::getPosition(window).x - (int)windowWidth / 2 + cameraPosition.x;
				int worldMouseY = sf::Mouse::getPosition(window).y - (int)windowWidth / 2 + cameraPosition.y;
				particles[particleCount] = (Particle(vec2f(worldMouseX, worldMouseY)));
				particleCount++;
				//particles.push_back(Particle(vec2f(-100.0f, 0.0f)));
				//std::cout << "LEFT" << std::endl;
				std::cout << tree.root->size << ",(" << tree.root->position.x << "," << tree.root->position.y << ")" << std::endl;
				tree.clear();
				//tree.fit(particles);
				for (int i = 0; i < particleCount; ++i) {
					std::cout << particles[i].position.x << "," << particles[i].position.y << std::endl;
					//tree.root->insert(&particles[i]);
				}
				
				tree.fill(particles, particleCount);
				tree.debugprint();
			}
				
		}
		
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		//	std::cout << "press!" << std::endl;
		//}
		//std::cout << worldMouseX << "," << worldMouseY << std::endl;
		window.clear(sf::Color::Black);
		window.setView(view);
		if (particleCount > 0) {
			for (auto particle : particles) {
				particle.draw(window);
			}
		}
		//tree.fill(particles);
		tree.draw(window);
		sf::Text mousePos(std::to_string(sf::Mouse::getPosition(window).x) + "," + std::to_string(sf::Mouse::getPosition(window).y), font);
		mousePos.setPosition(-400, -400);
		mousePos.setCharacterSize(16);
		mousePos.setStyle(sf::Text::Bold);
		mousePos.setFillColor(sf::Color::White);
		float x = sf::Mouse::getPosition(window).x;
		float y = sf::Mouse::getPosition(window).y;
		std::string st = std::to_string(tree.root->contains(&Particle(vec2f(x-400, y-400))));
		sf::Text checkPos(st, font);
		checkPos.setPosition(-300, -400);
		checkPos.setCharacterSize(16);
		checkPos.setFillColor(sf::Color::White);
		window.draw(mousePos);
		window.draw(checkPos);
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
