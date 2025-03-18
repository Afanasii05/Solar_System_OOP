#pragma once
#include <string>
#include "CelestialEntity.h"
class Sun:public CelestialEntity
{
private:
	int temperature;
	std::string color;
	std::string name;

public:
	Sun(int size, float positions[2],float initialVelocity, int temperature,std::string color,std::string name);
	~Sun();
};

