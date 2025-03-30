#pragma once
#include<string>
#include <SFML/Graphics.hpp>
class CelestialEntity
{
protected:	
	float size;
	float position[2] = {0.f, 0.f};
	std::string type="unknown";
	sf::Vector2f velocity = { 0.f, 0.f };
public:
	CelestialEntity(float size);
	virtual ~CelestialEntity();

	void setType(std::string type);
	std::string getType() {return type;}

	float getSize() const;

	sf::Vector2f getPosition() const { return  { position[0],position[1]}; }
	void setPosition(sf::Vector2f pos) { position[0] = pos.x;position[1] = pos.y; }


	void setVelocity(sf::Vector2f vel) { velocity = vel; }
	sf::Vector2f getVelocity() { return velocity; }
	virtual bool checkTemperature() = 0;
	virtual float getMass() = 0;
};

