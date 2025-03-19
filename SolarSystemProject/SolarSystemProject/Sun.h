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
	Sun(int size, int positions[2],float initialVelocity, int temperature,std::string color,std::string name);
	bool checkTemperature() override;
	void increaseTemperature() override;
    int getTemperature() const;
	~Sun();
};

