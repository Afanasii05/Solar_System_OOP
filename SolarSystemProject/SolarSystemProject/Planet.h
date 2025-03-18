#pragma once
#include <string>
#include "CelestialEntity.h"
#include "Sun.h"
class Planet :public CelestialEntity
{
private:
	bool habitable;
	std::string name;
	float distance_from_sun;
	float temperature;
	

public:
	Planet(int size, float positions[2], float initialVelocity, bool habitable, std::string name,float temperature,float distance_from_sun);
	bool checkTemperature() override;
	void increaseTemperature() override;
	~Planet();
};

