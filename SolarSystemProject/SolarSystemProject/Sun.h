#pragma once
#include <string>
#include "CelestialEntity.h"
#include "SolarSpace.h"
class Sun:public CelestialEntity
{
private:
	float temperature;
	std::string color;
	std::string name;
	float density = 695000;
	
public:
	Sun(float size, int temperature,std::string name);

	bool checkTemperature() override;
	std::string getName() { return name; }
	float getMass() override { return size * density; }
	float getTemperature() { return temperature; }
	void increaseTemperature() { temperature += 10; }
	

	~Sun();
};

 