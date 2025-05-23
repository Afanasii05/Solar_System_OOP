#pragma once
#include "CelestialEntity.h"
#include "SolarSpace.h"
class BlackHole:public CelestialEntity
{

public:
	float getMass() override { return size * density+20; }
	BlackHole(float size, std::string name, std::string color);
	~BlackHole() {};

	
};

