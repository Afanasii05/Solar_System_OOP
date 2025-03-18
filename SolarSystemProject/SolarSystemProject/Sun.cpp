#include "Sun.h"
#include <string>
#include "CelestialEntity.h"
#include <iostream>

Sun::Sun(int size, float positions[2], float initialVelocity, int temperature, std::string color, std::string name) :CelestialEntity(size, positions, initialVelocity) {
	this->temperature = temperature;
	this->color = color;
	this->name = name;
	std::cout << "Sun " << name << " created" << std::endl;
	setType("Sun");

}

Sun::~Sun() {
    std::cout << "Sun " << name << " destroyed" << std::endl;
}
