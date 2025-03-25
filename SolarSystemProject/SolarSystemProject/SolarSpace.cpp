#include "SolarSpace.h"
#include <cmath>

std::vector<Sun*> SolarSpace::suns;
std::vector<Planet*> SolarSpace::planets;

std::tuple<int, int> SolarSpace::getSpaceSize()
{
	return {size_x, size_y};
}

void SolarSpace::addSun(Sun* sun)
{
	suns.push_back(sun);
}

void SolarSpace::addPlanet(Planet* planet)
{
	planets.push_back(planet);
}

std::vector<sf::CircleShape> SolarSpace::createSpriteSun()
{
	std::vector<sf::CircleShape> sunSprites;
	for (auto sun : suns) 
		sunSprites.push_back(createSpriteEntity(sun));
	return sunSprites;

}
Sun* SolarSpace::findClosestEntity() {
	Sun* clossestSun = nullptr;
	for (auto planet : planets) {
		auto [x_planet, y_planet] = planet->getPosition();
		std::string nume_soare;
		float min = 100000000000000;
		for (auto sun : suns) {
			auto [x_sun, y_sun] = sun->getPosition();
			float distance = sqrt(pow(x_planet-x_sun,2)+pow(y_planet-y_sun,2)) +planet->getSize()/2+sun->getSize()/2;
			if (distance < min) {
				min = distance;
				clossestSun = sun;
			}
		}
		return clossestSun;
	}
}
std::vector<sf::CircleShape> SolarSpace::createSpritePlanets()
{
	std::vector<sf::CircleShape> planetSprites;
	for (auto planet : planets) 
		planetSprites.push_back(createSpriteEntity(planet));
	return planetSprites;
}

sf::CircleShape SolarSpace::createSpriteEntity(CelestialEntity* entity)
{
		auto [x,y] = entity->getPosition();
		auto [width, height] = SolarSpace::getSpaceSize();
		sf::CircleShape entitySprite(entity->getSize());
		entitySprite.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
		entitySprite.setOrigin(entitySprite.getGeometricCenter());
		if (entity->getType() == "Sun")
			entitySprite.setFillColor(sf::Color::Yellow);
		else if (entity->getType() == "Planet")
			entitySprite.setFillColor(sf::Color::Blue);
		return entitySprite;
	
}


SolarSpace::~SolarSpace() {};