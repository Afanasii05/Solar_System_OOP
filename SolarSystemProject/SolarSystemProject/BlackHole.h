#pragma once
#include "CelestialEntity.h"
#include "SolarSpace.h"
class BlackHole:public CelestialEntity
{
private:
	float density = 200000000;
public:
	float getMass() override { return size * density; }
	bool checkTemperature() override { return true; };
	BlackHole(float size, std::string name, std::string color, SolarSpace* space);
	~BlackHole() {};

	
};

