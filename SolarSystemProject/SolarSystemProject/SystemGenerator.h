#pragma once
#include "SolarSpace.h"
#include "CelestialEntity.h"
#include "Sun.h"
#include "Planet.h"
#include <string>
class SystemGenerator
{
	int  numberOfPlanets=3;
	float nextMinimumSunPos;
	sf::Vector2f positionOfSun;
	std::string colors[10] = {
	"purple", "blue", "green", "red", "yellow",
	"cyan", "magenta", "orange", "pink", "gold"
	};



	public:
		SystemGenerator(sf::Vector2f positionOfSun, int numberOfPlanets, SolarSpace* space);
		void generateSystem(SolarSpace* space);
		float randomNumber(float lowerRange, float lowerMiddleRange, float upperMiddleRange, float upperRange) const;
		float distance(CelestialEntity* body1, CelestialEntity* body2) const;
		void setNextMinimumSunPos(float nextMinimumSunPos) { this->nextMinimumSunPos = nextMinimumSunPos; }
		float getNextMinimumSunPos() const { return nextMinimumSunPos; }
		int randomNumber(float lowerRange, float upperRange);	
};

