#pragma once
#include "CelestialEntity.h"
#include "SolarSpace.h"
#include <string>
#include <iostream>
class Asteroid:public CelestialEntity
{private:
	float impactDamage = 10;
	float defaultSpeed = 100;
	float power = 6000.f;
public:
	Asteroid(float size, const std::string name, const std::string color);
	float getMass() override { return size * density; }
	void setDamage(float damage) { this->impactDamage = damage; }
	float getPower() { return power; }
	std::string getType() { return type; }
	float getImpactDamage() { return impactDamage; }
	~Asteroid() { std::cout << "DeletedAsteroid\n"; };

};

 