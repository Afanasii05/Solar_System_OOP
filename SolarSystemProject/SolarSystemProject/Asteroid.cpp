#include "Asteroid.h"
#include <string>
#include "CelestialEntity.h"
#include <iostream>

//Constructor Asteroizi
Asteroid::Asteroid(float size, const std::string name, const std::string color) : CelestialEntity(size, name, color) {
		std::cout << "CreatedAsteroid\n";
		density = 10;
}
