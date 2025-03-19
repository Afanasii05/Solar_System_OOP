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
	float temperature=0;
	

public:
	Planet(int size, int positions[2], float initialVelocity, bool habitable, std::string name, float distance_from_sun);
	bool checkTemperature() override;
	void increaseTemperature() override;
	~Planet();
};

