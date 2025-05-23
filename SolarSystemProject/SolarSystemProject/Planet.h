#pragma once
#include <string>
#include "CelestialEntity.h"

// Forward declaration of SolarSpace
class SolarSpace;

class Planet : public CelestialEntity
{
private:
	float health = 100;
    

public:
    Planet(float size, std::string name, std::string color, SolarSpace* space);

    //functii get
    float getMass() override { return size * density; }
	float getHealth() { return health; }
	void setHealth(float health) { this->health = health; }

    ~Planet();
};