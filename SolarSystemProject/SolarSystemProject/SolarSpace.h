#pragma once
#include <vector>
#include <unordered_map>
#include "CelestialEntity.h"
#include "Planet.h"
#include "Sun.h" 
#include "BlackHole.h"
#include <SFML/Graphics.hpp>
#include "Asteroid.h"
class Sun;
class BlackHole;
class Asteroid;
class SolarSpace
{
private:
	sf::Texture sunTexture,blackHoleTexture,planetTexture;
	static const int size_x = 1920;
	static const int size_y = 1080;
	std::vector<Sun*> suns;
	std::vector<Planet*> planets;
	std::vector<CelestialEntity*> asteroids;
	std::vector<BlackHole*> blackHoles;
	std::vector<CelestialEntity*> celestialBodies;
	sf::Font font;
	sf::Vector2f mousePos;
	int sun_pos_index = 0;
	const float GravitationalConstant = 1.35f, size_for_blackHole=2500;
	const float errorConstant = 100;
	bool mousePressed = false;

	

public:

	SolarSpace();

	void addSun(Sun* sun);
	void addPlanet(Planet* planet);
	void addBlackHole(BlackHole* hole);
	void addAsteroid(Asteroid* asteroid);
	void updateCelestialBodiesGravity(float deltaTime) const;
	void setInitialVelocity(CelestialEntity* planet, float speedMultiplier);
	void clearSpace();
	void callAction();
	void definePlanetPosition(int sun_index, float sun_size, sf::Vector2f sun_pos);
	void updateCelestialBodiesColision();
	void updateSuntoBlackHole(CelestialEntity* body);
	void SetMousePos(sf::Vector2f mousePos) { this->mousePos = mousePos; }
	void setMousePressed(bool mousePressed) { this->mousePressed = mousePressed; }
	void createAsteroids(int number);
	void updateAsteroids();
	void updateAsteroidColision();

	std::vector<sf::CircleShape> createSpriteCelestialBody();
	sf::CircleShape createSpriteEntity(CelestialEntity* entity) const;
	sf::CircleShape createGlowSprite(CelestialEntity* entity) const;
	sf::Vector2f computeGravity(CelestialEntity* body1, CelestialEntity* body2) const;
	sf::Vector2f defineSunPosition(float size);
	sf::Color convertColor(std::string) const;
	sf::Text entityOnHoverText(CelestialEntity* entityOnHover);
	std::vector<sf::Text> createTextEntity();
	sf::Vector2f getHoverPos(sf::Vector2f defaultPosView);

	CelestialEntity* findStrongestEntity(CelestialEntity* planet);
	bool entityOnHover(CelestialEntity* entity);
	bool checkColision(CelestialEntity* body1, CelestialEntity* body2);
	float setTemperature(Planet* planet) const;
	float getRandomNumber(float lowerRange, float upperRange) const;
	

	~SolarSpace();
};
