#include "CelestialEntity.h"
#include <iostream>
#include "SolarSpace.h"
#include <string>
CelestialEntity::CelestialEntity(float size, std::string name, std::string color)//constructor pt clasa de baza
{
	this->size = size;
	this->name = name;
	this->color = color;
	std::cout << "CelestialEntity created" << std::endl;
}
void CelestialEntity::setType(std::string type)//ce fel de tip e(planeta, soare...)
{
	this->type = type;
}
float CelestialEntity::getSize() const//marimea 
{
	return size;
}
void CelestialEntity::setSize(float size){
	this->size = size;
}
CelestialEntity::~CelestialEntity()//destructor virtual
{
	std::cout << "CelestialEntity destroyed" << std::endl;
}


