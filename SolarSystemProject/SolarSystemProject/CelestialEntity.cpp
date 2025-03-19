#include "CelestialEntity.h"
#include <iostream>
#include <string>
CelestialEntity::CelestialEntity(int size, int position[2], float initialVelocity)
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
int CelestialEntity::getSize() const
{
	return size;
}

void CelestialEntity::CheckVelocitybyType()
{
	if (type == "Sun") {
		if (initialVelocity > 25) {
			std::cout << "The velocity of the sun is too high\nit will be set to 25(it's max velocity)" << std::endl;
			initialVelocity = 25;
		}
		else {
			std::cout << "The velocity of the sun is normal" << std::endl;
		}
	}
}
CelestialEntity::~CelestialEntity()
{
	std::cout << "CelestialEntity destroyed" << std::endl;
}


