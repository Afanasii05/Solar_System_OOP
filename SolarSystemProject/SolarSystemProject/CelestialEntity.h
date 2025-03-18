#pragma once
#include<string>
class CelestialEntity
{
private:
	int size;
	float position[2];
	float initialVelocity;

	std::string type="unknown";
public:
	CelestialEntity(int size, float position[2], float initialVelocity);
	virtual ~CelestialEntity();
	void setType(std::string type);
	void CheckVelocitybyType();
	virtual bool checkTemperature() = 0;
	virtual void increaseTemperature() = 0;

};

