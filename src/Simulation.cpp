#include "Simulation.h"

std::string round_to_digits(float value, int digits)
{
	std::string s = std::to_string(value);
	std::string out = "";
	for (auto c : s) {
		if (!(c == (char)".")) {
			if (digits > 0) {
				out += c;
				digits--;
			}
		}
		else {
			out += c;
		}
	}
	return out;
}

float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

Particle::Particle() :
	position(vec2f()) {}

Particle::Particle(vec2f pos) :
	position(pos) {}

//template<typename T>

void Body::update(Tree<Body> tree, float deltaTime) {
	vec2f a1 = tree.getAcceleration(position);
	//std::cout << "pos: " << position << std::endl;
	position = position + velocity * deltaTime + a1 * 0.5f*deltaTime*deltaTime;
	//std::cout << "pos: " << position << std::endl;
	vec2f a2 = tree.getAcceleration(position);
	//std::cout << "vel: " << velocity << std::endl;
	velocity = velocity + (a1 + a2)*0.5f*deltaTime;
	//std::cout << "vel: " << velocity << std::endl;
	//std::cout << "a1: " << a1 << "a2: " << a2 << std::endl;
}

float Body::getRadius() {
	float volume = mass / density;
	return std::cbrt((3 / (4 * 3.14159265358979323846)) * volume);
}

void Body::print()
{
	std::cout << "Body at " << this << "\n	position: " << position << "\n	mass: " << mass << "\n";
}

void Body::draw(float distanceScale, float radiusScale, sf::RenderWindow & targetWindow) {
	//sf::CircleShape planet(mass*radiusScale);
	//float radius = getRadius()*radiusScale;
	float radius = 5.0f;
	//std::cout << radius * radiusScale << std::endl;
	sf::CircleShape planet(radius);
	planet.setOrigin(radius, radius);
	planet.setPosition(position.x * distanceScale, position.y * distanceScale);
	planet.setFillColor(sf::Color::White);
	targetWindow.draw(planet);
}

void Body::debugInfo(sf::RenderWindow & targetWindow, sf::Font font) {
	std::string roundedMass = round_to_digits(mass, 2);
	std::string roundedvx = round_to_digits(velocity.x, 2);
	std::string roundedvy = round_to_digits(velocity.y, 2);
	std::string st = roundedMass + "kg" + " " + roundedvx + "ms^-1 x," + roundedvy + "ms^-1 y";
	sf::Text info(st, font);
	//std::cout << position.x / 1e-7 << std::endl;
	info.setPosition(std::truncf(position.x*1e-7), std::truncf(position.y*1e-7));
	info.setCharacterSize(15);
	info.setFillColor(sf::Color::Red);
	targetWindow.draw(info);
}

Simulation::Simulation(float posrange, float masslower, float masshigher, int nbodies, float deltatime) :
	posRange(posrange), massLower(masslower), massHigher(masshigher), nBodies(nbodies), deltaTime(deltatime), bodies(new Body[nBodies]), tree(Tree<Body>(bodies, nBodies)) 
{
	for (int i = 0; i < nBodies; ++i) {
		bodies[i].position = vec2f::random(-posRange, posRange);
		bodies[i].mass = RandomFloat(massLower, massHigher);
	}
	//for (int i = 0; i < nBodies; ++i) {
	//	bodies[i].print();
	//}
	tree.fit(bodies, nBodies);
}

void Simulation::step() {
	tree.clear();
	tree.fill(bodies, nBodies);
	for (int i = 0; i < nBodies; ++i) {
		typedef Tree<Particle> QT;
		bodies[i].update(tree, deltaTime);
	}
}

void Simulation::draw(float scale, sf::RenderWindow & targetWindow) {
	for (int i = 0; i < nBodies; ++i) {
		bodies[i].draw(scale, scale, targetWindow);
	}
	//tree.root->draw(scale, targetWindow);
}
