#include "Sun.h"
#include <string>
#include "CelestialEntity.h"
#include <iostream>

Sun::Sun(float size, std::string name,std::string color,SolarSpace* space) : CelestialEntity(size,name,color) {
	setType("Sun");
	space->addCelBody(this);
	std::cout << "CreatedSun\n";
	density = 895000;
}

Sun::~Sun() {
    std::cout << "Sun " << name << " destroyed" << std::endl;
}
