#include "SystemGenerator.h"
#include <random>
#include <ctime>
#include <cmath>
SystemGenerator::SystemGenerator(sf::Vector2f positionOfSun,  int numberOfPlanets, SolarSpace* space)
{
	this->positionOfSun = positionOfSun;
	this->numberOfPlanets = numberOfPlanets;
	generateSystem(space);

}
void SystemGenerator::generateSystem(SolarSpace* space)
{
	float mx = 0;
	Sun* sun = new Sun(randomNumber(450,650), "Sun", "Yellow", space);
	space->setInitialVelocity(sun, 20.f);
	sun->setPosition(positionOfSun);
	int randomiserIndex = sun->getSize() + 1500;
	for (int i = 0; i < numberOfPlanets; i++) {
		Planet* planet = new Planet(randomNumber(100,230), "Planet" + std::to_string(i), colors[randomNumber(0,10)], space);
		float x = positionOfSun.x + randomNumber(-4000.f - randomiserIndex * (i + 1), -2000.f - randomiserIndex * (i + 1),
			2000.f + randomiserIndex * (i + 1), 4000.f + randomiserIndex * (i + 1));
		float y = positionOfSun.y + randomNumber(-4000.f - randomiserIndex * (i + 1), -2000.f - randomiserIndex * (i + 1),
			2000.f + randomiserIndex * (i + 1), 4000.f + randomiserIndex * (i + 1));
		planet->setPosition({ x,y });
		space->setInitialVelocity(planet, sqrt(1.4f*sun->getMass()/distance(sun,planet)));
		if (abs(x) > mx)
			mx = planet->getPosition().x;
	}
	setNextMinimumSunPos(mx);
}

int SystemGenerator::randomNumber(float lowerRange, float upperRange) {
	static std::mt19937 rng(static_cast<unsigned>(time(nullptr)));
	std::uniform_real_distribution<float> dist(lowerRange, upperRange);
	return dist(rng);

}
float SystemGenerator::randomNumber(float lowerRange,float lowerMiddleRange, float upperMiddleRange, float upperRange) const {

	static std::mt19937 chance(static_cast<unsigned>(time(nullptr)));
	std::uniform_real_distribution<float> dist(0, 1);
	static std::mt19937 rng(static_cast<unsigned>(time(nullptr)));
	if (dist(chance) < 0.5f) {
		std::uniform_real_distribution<float> dist(lowerRange, lowerMiddleRange);
		return dist(rng);
	}
	else {
		std::uniform_real_distribution<float> dist(upperMiddleRange, upperRange);
		return dist(rng);
	}
	return 0;


}
float SystemGenerator::distance(CelestialEntity* body1, CelestialEntity* body2) const {
	auto [x_body1, y_body1] = body1->getPosition();
	auto [x_body2, y_body2] = body2->getPosition();
	return sqrt(pow(x_body2 - x_body1, 2) + pow(y_body2 - y_body1, 2));
}