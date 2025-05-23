#include "SystemGenerator.h"
#include <random>
#include <ctime>
#include "Vec2.h"
#include <cmath>
//creez un spatiu format dintr-un soare si un numar de planete 
SystemGenerator::SystemGenerator(Math::Vec2<float> positionOfSun,  int numberOfPlanets, SolarSpace* space)
{
	this->positionOfSun = positionOfSun;
	this->numberOfPlanets = numberOfPlanets;
	_generateSystem(space);//apelez functia de generare in constructor

}
void SystemGenerator::_generateSystem(SolarSpace* space)
{
	float mx = 0;
	Sun* sun = new Sun(randomNumber(450,650), "Sun", "Yellow", space);//creez soarele
	space->setInitialVelocity(sun, 20.f);//ii ofer un initial velocity mic
	sun->setPosition(Math::ToSF(positionOfSun));//ii setez pozitia
	int randomiserIndex = sun->getSize() + 1500;//pt a determina pozitiile celorlalte planete fata de marimea si distanta de la soare
	for (int i = 0; i < numberOfPlanets; i++) {
		Planet* planet = new Planet(randomNumber(100,230), "Planet" + std::to_string(i), colors[(int)randomNumber(0,10)], space);//o planeta cu culoare si marime random
		Math::Vec2<float> randomVec = {//ii setez o distanta random in functie de celelalte planete(indexul lui i) dar si marimea soarelui
		   randomNumber(distFromPlanets.x - randomiserIndex * (i + 1), -distFromPlanets.y - randomiserIndex * (i + 1), distFromPlanets.y + randomiserIndex * (i + 1), -distFromPlanets.x + randomiserIndex * (i + 1)),
		randomNumber(distFromPlanets.x - randomiserIndex * (i + 1), -distFromPlanets.y - randomiserIndex * (i + 1), distFromPlanets.y + randomiserIndex * (i + 1), -distFromPlanets.x + randomiserIndex * (i + 1))
        };
		
		planet->setPosition({ Math::ToSF<float>(positionOfSun + randomVec) });
		std::cout << planet->getPosition().x << ' ' << planet->getPosition().y << '\n';
		space->setInitialVelocity(planet, sqrt(1.4f*sun->getMass()/distance(sun,planet)));//un velocity folosind o formula pt a calcula o orbita perfecta
		if (abs(planet->getPosition().x) > mx)//pt a crea un alt spatiu la o distanta potrivita
			mx = planet->getPosition().x;
	}
	setNextMinimumSunPos(mx);
}

float SystemGenerator::randomNumber(float lowerRange, float upperRange) {//random number generator
	static std::mt19937 rng(static_cast<unsigned>(time(nullptr)));
	std::uniform_real_distribution<float> dist(lowerRange, upperRange);
	return dist(rng);

}
//random number generator compus din 2 intervale 
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
//formula de distanta
float SystemGenerator::distance(CelestialEntity* body1, CelestialEntity* body2) const {
	auto [x_body1, y_body1] = body1->getPosition();
	auto [x_body2, y_body2] = body2->getPosition();
	return sqrt(pow(x_body2 - x_body1, 2) + pow(y_body2 - y_body1, 2));
}