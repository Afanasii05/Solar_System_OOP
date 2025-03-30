#include "Sun.h"
#include <string>
#include "CelestialEntity.h"
#include <iostream>

Sun::Sun(float size, int temperature, std::string name) : CelestialEntity(size) {
	this->temperature = temperature;
	this->name = name;
	std::cout << "Sun " << name << " created" << std::endl;
	setType("Sun");
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
