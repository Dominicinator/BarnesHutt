#pragma once
#include "Simulation.h"
class World
{
public:
	//Simulation sim(1E9f, 1E20, 1E22, 5, 10000.0f);
	float scale;
	Simulation sim;
	World();
	World(float posRange, float masslower, float masshigher, float nBodies, float deltaTime);
	virtual ~World();

	void draw(sf::RenderWindow& targetWindow);
	void update();
};

