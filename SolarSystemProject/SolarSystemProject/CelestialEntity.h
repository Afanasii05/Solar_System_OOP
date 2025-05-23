#pragma once
#include<string>
#include <SFML/System/Vector2.hpp>
class CelestialEntity
{
protected:
	float size, position[2] = { 0.f, 0.f };//pozitia si marimea unui obiect
	std::string type = "unknown", name, color;
	sf::Vector2f velocity = { 0.f, 0.f };
	float density = 0.f;
public:
	CelestialEntity(float size, std::string name, std::string color);
	virtual ~CelestialEntity();

	void setType(std::string type);
	std::string getType() { return type; }

	float getSize() const;
	void setSize(float size);

	sf::Vector2f getPosition() const { return  { position[0],position[1] }; }
	void setPosition(sf::Vector2f pos) { position[0] = pos.x;position[1] = pos.y; }
	std::string getName() const { return name; }

	void setVelocity(sf::Vector2f vel) { velocity = vel; }
	sf::Vector2f getVelocity() const { return velocity; }
	virtual float getMass() = 0;
	std::string getColor() { return color; }
};
