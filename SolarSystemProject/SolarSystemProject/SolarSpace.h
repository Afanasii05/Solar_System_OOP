
#pragma once
#include <vector>
#include <iostream>
#include<tuple>
#include "CelestialEntity.h"
#include "Planet.h"
#include "Sun.h"
#include <SFML/Graphics.hpp>
class SolarSpace
{
private:
	static const int size_x = 640;
	static const int size_y = 320;
	static std::vector<Sun*> suns;
	static std::vector<Planet*> planets;

protected:
	const float GravitationalConstant = 1.2;
	
	
public:
	SolarSpace() {};
	static std::tuple<int, int> getSpaceSize();
	static void addSun(Sun* sun);
	static void addPlanet(Planet* planet);
	std::vector<sf::CircleShape> createSpriteSun();
	std::vector<sf::CircleShape> createSpritePlanets();
	sf::CircleShape createSpriteEntity(CelestialEntity* entity);
	Sun* findClosestEntity();


	sf::Vector2f computeGravity(Sun* sun, Planet* planet) const {
		auto [x_planet, y_planet] = planet->getPosition();
		auto [x_sun, y_sun] = sun->getPosition();
		float distance = sqrt(pow(x_planet - x_sun, 2) + pow(y_planet - y_sun, 2)) + planet->getSize() / 2 + sun->getSize() / 2;

		if (distance < 10.f) return { 0.f, 0.f }; 
		sf::Vector2f direction = { x_sun - x_planet, y_sun - y_planet };
		direction /= distance;
		float force = GravitationalConstant * (sun->getMass() * planet->getMass()) / (distance * distance);
		sf::Vector2f acceleration = direction * (force / planet->getMass());

		return acceleration; 
	}
	void updatePlanets(float deltaTime) const {
		for (auto planet : planets) {
			sf::Vector2f totalAcceleration(0.f, 0.f);

			for (auto sun : suns) {
				totalAcceleration += computeGravity(sun, planet);
			}

			planet->setVelocity(planet->getVelocity() + totalAcceleration * deltaTime);  
			planet->setPosition( planet->getPosition()+ planet->getVelocity() * deltaTime);  
		}
	}
	void setInitialVelocity(Planet* planet, float speedMultiplier) {
		Sun* sun = findClosestEntity();
		sf::Vector2f direction = planet->getPosition() - sun->getPosition();
		float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		sf::Vector2f tangentVelocity(-direction.y, direction.x); 
		planet->setVelocity ((tangentVelocity / distance) * speedMultiplier);
	} 
	
	~SolarSpace();


};

