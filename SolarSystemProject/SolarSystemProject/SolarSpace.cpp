#include "SolarSpace.h"
#include <cmath>
void SolarSpace::addSun(Sun* sun)  
{suns.push_back(sun);
sun->setPosition(defineSunPosition(sun->getSize()));
}


void SolarSpace::addPlanet(Planet* planet)
{planets.push_back(planet);}

sf::Vector2f SolarSpace::defineSunPosition(float size)
{
	if (sun_pos_index == 0) {
		sun_pos_index += 1;
		return { 0.f,0.f };
	}
	sun_pos_index += 1;
	return { sun_pos_index * 3000.f , 0.f };
	
}

void SolarSpace::definePlanetPosition(int sun_index, float sun_size, sf::Vector2f sun_pos)
{

}

std::vector<sf::CircleShape> SolarSpace::createSpriteSun()
{
	std::vector<sf::CircleShape> sunSprites;
	for (auto sun : suns) 
		sunSprites.push_back(createSpriteEntity(sun));
	return sunSprites;
}

std::vector<sf::CircleShape> SolarSpace::createSpritePlanets()
{
	std::vector<sf::CircleShape> planetSprites;
	for (auto planet : planets)
		planetSprites.push_back(createSpriteEntity(planet));
	return planetSprites;
}

CelestialEntity* SolarSpace::findStrongestEntity(CelestialEntity* body) {
	CelestialEntity* clossestEntity = nullptr;
	auto [x_planet, y_planet] = body->getPosition();
	float mx = -1;
	for (auto sun : suns) {
		auto [x_sun, y_sun] = sun->getPosition();
		float distance = sqrt(pow(x_planet-x_sun,2)+pow(y_planet-y_sun,2));
		float grav =  sun->getMass() / distance;
		if (grav >mx && distance >10.f) {
			mx = grav;
			clossestEntity = sun;
		}
	}
	for (auto otherPlanet : planets) {
		auto [x_sun, y_sun] = otherPlanet->getPosition();
		float distance = sqrt(pow(x_planet - x_sun, 2) + pow(y_planet - y_sun, 2));
		float grav = otherPlanet->getMass() / distance;
		if (grav > mx && distance > 10.f) {
			mx = grav;
			clossestEntity = otherPlanet;
		}
	}
	return clossestEntity;
}


sf::Vector2f SolarSpace::computeGravity(CelestialEntity* body1, CelestialEntity* body2) const
{
	auto [x_body2, y_body2] = body2->getPosition();
	auto [x_body1, y_body1] = body1->getPosition();
	float distance = sqrt(pow(x_body2 - x_body1, 2) + pow(y_body2 - y_body1, 2)) + errorConstant;

	if (distance < 50.f) 
		return { 0.f, 0.f };
	sf::Vector2f direction = { x_body1-x_body2, y_body1 - y_body2};
	direction /= distance;
	float force = GravitationalConstant * (body1->getMass()) / (distance * distance);

	sf::Vector2f acceleration =  direction * force;

	return acceleration;
}
void SolarSpace::updatePlanets(float deltaTime) const
{
	for (auto planet : planets) {
		sf::Vector2f totalAcceleration(0.f, 0.f);
		for (auto sun : suns) 
			totalAcceleration += computeGravity(sun, planet);
		
		for (auto otherPlanet : planets) 
			if (otherPlanet != planet) 
				totalAcceleration += computeGravity(otherPlanet, planet);
			
		planet->setVelocity(planet->getVelocity() + totalAcceleration * deltaTime);
		planet->setPosition(planet->getPosition() + planet->getVelocity() * deltaTime);
		planet->setTemperature(setTemperature(planet));
	}
	deltaTime *= 0.5;
	for (auto sun : suns) {
		sf::Vector2f totalAcceleration(0.f, 0.f);
		for (auto planet : planets)
			totalAcceleration += computeGravity(planet, sun);

		for (auto otherSun : suns)
			if (otherSun != sun)
				totalAcceleration += computeGravity(otherSun, sun);

		sun->setVelocity(sun->getVelocity() + totalAcceleration * deltaTime);
		sun->setPosition(sun->getPosition() + sun->getVelocity() * deltaTime);
	}
}

void SolarSpace::setInitialVelocity(CelestialEntity* body, float speedMultiplier)
{
	CelestialEntity* bodyy = findStrongestEntity(body);
	sf::Vector2f direction = body->getPosition() - bodyy->getPosition();
	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	sf::Vector2f tangentVelocity(-direction.y, direction.x);
	body->setVelocity((tangentVelocity / distance) * speedMultiplier);
}


sf::CircleShape SolarSpace::createSpriteEntity(CelestialEntity* entity)
{
	static  float factorScale = 2.1;
	static  float growingRate = 0.02f;
		auto [x,y] = entity->getPosition();
		sf::CircleShape entitySprite(entity->getSize());
		entitySprite.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
		entitySprite.setOrigin(entitySprite.getGeometricCenter());
		if (entity->getType() == "Sun") {
			entitySprite.setFillColor(sf::Color::Yellow);
			if (factorScale >= 3.5)
				growingRate *= -1;
			else if (factorScale < 2) 
				growingRate *= -1;
			
			entitySprite.scale({ sqrt(factorScale),sqrt(factorScale)});
			factorScale += growingRate;
		}

		else if (entity->getType() == "Planet")
			entitySprite.setFillColor(sf::Color::Blue);
		return entitySprite;
	
}

float SolarSpace::setTemperature(Planet* planet) const
{
	float total_temperature = 0;
	for (auto sun : suns) {
		auto [x_planet, y_planet] = planet->getPosition();
		auto [x_sun, y_sun] = sun->getPosition();
		float distance = sqrt(pow(x_planet - x_sun, 2) + pow(y_planet - y_sun, 2)) + planet->getSize() / 2 + sun->getSize() / 2;
		total_temperature += sun->getTemperature() / distance;
	}
	return total_temperature;
}
SolarSpace::~SolarSpace() {};