#pragma once
#include "SolarSpace.h"
#include "CelestialEntity.h"
#include "Sun.h"
#include "Vec2.h"
#include "Planet.h"
#include <string>
class SystemGenerator
{
	int  numberOfPlanets=3;
	float nextMinimumSunPos;
	Math::Vec2<int> distFromPlanets{ -5000,2500 };
	Math::Vec2<float> positionOfSun;
	std::string colors[10] = {
	"purple", "blue", "green", "red", "yellow",
	"cyan", "magenta", "orange", "pink", "gold"
	};
	void _generateSystem(SolarSpace* space);
	float randomNumber(float lowerRange, float lowerMiddleRange, float upperMiddleRange, float upperRange) const;
	void setNextMinimumSunPos(float nextMinimumSunPos) { this->nextMinimumSunPos = nextMinimumSunPos; }

	float distance(CelestialEntity* body1, CelestialEntity* body2) const;
	float randomNumber(float lowerRange, float upperRange);
	public:
		SystemGenerator(Math::Vec2<float> positionOfSun, int numberOfPlanets, SolarSpace* space);
		float getNextMinimumSunPos() const { return nextMinimumSunPos; }
			
};

