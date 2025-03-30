#include "CelestialEntity.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "SolarSpace.h"
#include <string>
CelestialEntity::CelestialEntity(float size)
{
	this->size = size;
	std::cout << "CelestialEntity created" << std::endl;
}
void CelestialEntity::setType(std::string type)
{
	this->type = type;
}
float CelestialEntity::getSize() const
{
	return size;
}

CelestialEntity::~CelestialEntity()
{
	std::cout << "CelestialEntity destroyed" << std::endl;
}


