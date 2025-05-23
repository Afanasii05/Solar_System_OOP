#pragma once
#include <string>
#include "CelestialEntity.h"
#include "SolarSpace.h"
class Sun:public CelestialEntity
{
public:
	Sun(float size, std::string name, std::string color, SolarSpace* space);

	//functii get
	float getMass() override { return size * density+10; }

	~Sun();
};

 