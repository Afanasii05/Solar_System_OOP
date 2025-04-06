#pragma once
#include <string>
#include "CelestialEntity.h"
#include "SolarSpace.h"
class Sun:public CelestialEntity
{
private:
	float density = 895000;

	
public:
	Sun(float size, std::string name, std::string color, SolarSpace* space);

	//functii get
	float getMass() override { return size * density; }
	float getTemperature() { return temperature; }
	void increaseTemperature() { temperature += 10; }
	bool checkTemperature() override;

	~Sun();
};

 