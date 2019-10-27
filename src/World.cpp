#include "World.h"



World::World() :
	sim(Simulation(1e9f, 1e20f, 1e22f, 5, 10000.0f)) {}

World::World(float posRange, float masslower, float masshigher, float nBodies, float deltaTime) : 
	sim(Simulation(posRange, masslower, masshigher, nBodies, deltaTime)) {}


World::~World()
{
}

void World::draw(sf::RenderWindow& targetWindow)
{
	sim.draw(scale, targetWindow);
}

void World::update()
{
	sim.step();
}


