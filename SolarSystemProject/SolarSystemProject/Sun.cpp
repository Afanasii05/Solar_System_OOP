#include "Sun.h"
#include <string>
#include "CelestialEntity.h"
#include <iostream>

Sun::Sun(float size, std::string name,std::string color,SolarSpace* space) : CelestialEntity(size,name,color) {
	
	
	setType("Sun");
	space->addSun(this);
	std::cout << "CreatedSun\n";

}

bool Sun::checkTemperature(){
	if(temperature >10000){
		std::cout << "The temperature of the sun " << name << " is too high\nIt exploded and destroyed everything in the area"<<std::endl;
		return true;
	}
	return false;
}


Sun::~Sun() {
    std::cout << "Sun " << name << " destroyed" << std::endl;
}
