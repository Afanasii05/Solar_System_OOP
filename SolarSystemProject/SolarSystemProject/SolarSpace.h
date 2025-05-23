#pragma once
#include <vector>
#include <unordered_map>
#include "CelestialEntity.h"
#include "Planet.h"
#include "Sun.h" 
#include "BlackHole.h"
#include <SFML/Graphics.hpp>
#include "Asteroid.h"
#include "TextureManager.h"
class Sun;
class BlackHole;
class Asteroid;
class SolarSpace
{
private:
	
	std::vector<Asteroid*> asteroids;
	std::vector<CelestialEntity*> celestialBodies;
	TextureManager mng;
	sf::Vector2f mousePos;
	const float GravitationalConstant = 1.35f, size_for_blackHole=2500;
	const float errorConstant = 100;
	bool mousePressed = false;

	sf::CircleShape createSpriteEntity(CelestialEntity* entity) const;
	sf::CircleShape createGlowSprite(CelestialEntity* entity) const;
	sf::Vector2f computeGravity(CelestialEntity* body1, CelestialEntity* body2) const;

	
	CelestialEntity* findStrongestEntity(CelestialEntity* planet);
	bool entityOnHover(CelestialEntity* entity);
	bool checkColision(CelestialEntity* body1, CelestialEntity* body2);
	void updateCelestialBodiesGravity(float deltaTime) const;
	void updateCelestialBodiesColision();
	void updateSuntoBlackHole(CelestialEntity* body);
public:

	SolarSpace();

	void createAsteroids(int number);
	void updateAsteroids();
	void updateAsteroidColision();
	std::vector<sf::CircleShape> createSpriteCelestialBody();
	sf::Text entityOnHoverText(CelestialEntity* entityOnHover);
	sf::Text createTextEntity();
	sf::Vector2f getHoverPos(sf::Vector2f defaultPosView);
	void addCelBody(CelestialEntity* body);

	void setInitialVelocity(CelestialEntity* planet, float speedMultiplier);

	void clearSpace();
	void callAction();

	

	void SetMousePos(sf::Vector2f mousePos) { this->mousePos = mousePos; }
	void setMousePressed(bool mousePressed) { this->mousePressed = mousePressed; }

	

	
	sf::Color convertColor(std::string) const;

	float getRandomNumber(float lowerRange, float upperRange) const;
	

	~SolarSpace();
};
