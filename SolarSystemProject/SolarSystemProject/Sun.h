#pragma once
#include <string>
#include "CelestialEntity.h"
class Sun:public CelestialEntity
{
private:
	int temperature;
	std::string color;
	std::string name;
	float density = 10000;

public:
	Sun(float size, float positions[2],float initialVelocity, int temperature,std::string color,std::string name);
	bool checkTemperature() override;
	void increaseTemperature() override;
	std::string getName() { return name; }
	float getMass() { return size * density; }


	~Sun();
};

