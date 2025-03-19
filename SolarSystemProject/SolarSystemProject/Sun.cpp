#include "Sun.h"
#include <string>
#include "CelestialEntity.h"
#include "SolarSpace.h"
#include <iostream>

Sun::Sun(int size, int positions[2], float initialVelocity, int temperature, std::string color, std::string name) :CelestialEntity(size, positions, initialVelocity) {
	this->temperature = temperature;
	this->color = color;
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
void Sun::increaseTemperature() {
	temperature+=2;
	std::cout<<"Sun " << name << ": " << temperature << '\n';
}
int Sun::getTemperature() const {
	return temperature;
}
Sun::~Sun() {
    std::cout << "Sun " << name << " destroyed" << std::endl;
}
