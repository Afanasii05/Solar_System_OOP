#include "CelestialEntity.h"
#include <iostream>
#include <string>
CelestialEntity::CelestialEntity(int size, float position[2], float initialVelocity)
{
	this->size = size;
	this->position[0] = position[0];
	this->position[1] = position[1];
	this->initialVelocity = initialVelocity;
	std::cout << "CelestialEntity created" << std::endl;
}
void CelestialEntity::setType(std::string type)
{
	this->type = type;
}
