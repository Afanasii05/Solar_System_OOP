#include "CelestialEntity.h"
#include <iostream>
#include "SolarSpace.h"
#include <string>
CelestialEntity::CelestialEntity(float size, std::string name, std::string color)
{
	this->size = size;
	this->name = name;
	this->color = color;
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
void CelestialEntity::setSize(float size){
	this->size = size;
}
CelestialEntity::~CelestialEntity()
{
	std::cout << "CelestialEntity destroyed" << std::endl;
}


