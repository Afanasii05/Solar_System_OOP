#include "Asteroid.h"
#include "SolarSpace.h"
#include <string>
#include "CelestialEntity.h"
#include <iostream>


Asteroid::Asteroid(float size, const std::string name, const std::string color, SolarSpace* space) : CelestialEntity(size, name, color) {
		std::cout << "CreatedAsteroid\n";
}
