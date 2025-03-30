#pragma once
#include <vector>
#include <iostream>
#include <tuple>
#include "CelestialEntity.h"
#include "Planet.h"
#include "Sun.h" 
#include <SFML/Graphics.hpp>
class Sun;
class SolarSpace
{
private:
	static const int size_x = 1920;
	static const int size_y = 1080;
	std::vector<Sun*> suns;
	std::vector<Planet*> planets;


	std::vector<std::vector<sf::Vector2f>> startingSpacePlanetPosition;
	std::vector<float> startingSpaceSunPosition;

	int sun_pos_index = 0;
	int sun_pos[3] = {0,0,0};

	const float GravitationalConstant = 1.2;
	const float errorConstant = 100;

public:

	SolarSpace() {};

	void addSun(Sun* sun);
	void addPlanet(Planet* planet);

	std::vector<sf::CircleShape> createSpriteSun();
	std::vector<sf::CircleShape> createSpritePlanets();
	sf::CircleShape createSpriteEntity(CelestialEntity* entity);

	CelestialEntity* findStrongestEntity(CelestialEntity* planet);

	
	sf::Vector2f defineSunPosition(float size);
	void definePlanetPosition(int sun_index,float sun_size,sf::Vector2f sun_pos);

	sf::Vector2f computeGravity(CelestialEntity* body1, CelestialEntity* body2) const;
	void updatePlanets(float deltaTime) const;
	void setInitialVelocity(CelestialEntity* planet, float speedMultiplier);
	float setTemperature(Planet* planet) const;
	~SolarSpace();
};
