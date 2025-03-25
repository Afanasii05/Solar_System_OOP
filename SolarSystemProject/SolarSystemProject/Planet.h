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
	float density = 1000;
	sf::Vector2f velocity = {0.f,0.f};

public:
	sf::Vector2f position; 
	
	Planet(float size, float positions[2], float initialVelocity, bool habitable, std::string name, float distance_from_sun);
	bool checkTemperature() override;
	void increaseTemperature() override;
	void setTemperature();
	std::string getName() { return name; }
    void  setVelocity(sf::Vector2f vel) { velocity = vel; }
	sf::Vector2f getVelocity() { return velocity; }
	float getMass() { return size * density; }
	~Planet();
};

