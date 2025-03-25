#pragma once
#include<string>
#include <SFML/Graphics.hpp>
class CelestialEntity
{
protected:	
	float size;
	float position[2];
	float initialVelocity;

	std::string type="unknown";
public:
	CelestialEntity(float size, float position[2], float initialVelocity);
	virtual ~CelestialEntity();
	void setType(std::string type);
	void CheckVelocitybyType();
	float getSize() const;
	sf::Vector2f getPosition() const { return { position[0],position[1]}; }
	virtual bool checkTemperature() = 0;
	virtual void increaseTemperature() = 0;
	std::string getType() { return type; }
    void setPosition(sf::Vector2f pos) { position[0] = pos.x; position[1] = pos.y; }
};

