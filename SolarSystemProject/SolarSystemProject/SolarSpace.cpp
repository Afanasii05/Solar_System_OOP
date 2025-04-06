#include "SolarSpace.h"
#include <cmath>
#include <ctime>
#include <random>
#include "Asteroid.h"
#include <iostream>

SolarSpace::SolarSpace() {
	if (!sunTexture.loadFromFile("sunTexture.png"))
		std::cout << "Fail!\n";
	sunTexture.setSmooth(true);
	if (!blackHoleTexture.loadFromFile("blackHoleTexture.jpg"))
		std::cout << "Fail!\n";
	blackHoleTexture.setSmooth(true);
	if (!planetTexture.loadFromFile("planetTexture.jpg")) 
		std::cout << "Fail!\n";
	planetTexture.setSmooth(true);
	if (!font.openFromFile("arial.ttf"))
		std::cout << "Failed to load font\n";
}

void SolarSpace::addSun(Sun* sun)  
{suns.push_back(sun);
celestialBodies.push_back(sun);
sun->setPosition(defineSunPosition(sun->getSize()));
}


void SolarSpace::addPlanet(Planet* planet)
{celestialBodies.push_back(planet);
	planets.push_back(planet);
}
void SolarSpace::addBlackHole(BlackHole* hole) {
	celestialBodies.push_back(hole);
}
void SolarSpace::addAsteroid(Asteroid* asteroid) {
	celestialBodies.push_back(asteroid);
	asteroids.push_back(asteroid);
}

sf::Vector2f SolarSpace::defineSunPosition(float size)
{
	if (sun_pos_index == 0) {
		sun_pos_index += 1;
		return { 0.f,0.f };
	}
	sun_pos_index += 1;
	float totalRange = sun_pos_index * 18500;
	float y_range = getRandomNumber(-1*totalRange, totalRange);
	return {totalRange-y_range, y_range};
}

void SolarSpace::definePlanetPosition(int sun_index, float sun_size, sf::Vector2f sun_pos)
{}

void SolarSpace::updateCelestialBodiesColision() {
	for (size_t i = 0; i < celestialBodies.size(); ++i) {
		CelestialEntity* body1 = celestialBodies[i];
		if (!body1) continue;

		for (size_t j = 0; j < celestialBodies.size(); ) {
			CelestialEntity* body2 = celestialBodies[j];
			if (!body2 || body1 == body2) {
				++j;
				continue;
			}

			if (checkColision(body1, body2)) {
				if (body1->getMass() > body2->getMass()) {
					body1->setSize(body1->getSize() + body2->getSize());
					celestialBodies.erase(celestialBodies.begin() + j);
					continue; // nu incrementăm j pentru că vectorul s-a modificat
				}
			}

			++j;
		}

		if (body1->getSize() >= size_for_blackHole && body1->getType() != "BlackHole") {
			updateSuntoBlackHole(body1); // Încă e valid
			celestialBodies.erase(celestialBodies.begin() + i);
			i--; // Decrementăm i pentru a verifica din nou poziția curentă
			continue;
			
		}
	}
}

void SolarSpace::updateSuntoBlackHole(CelestialEntity* body) {
	BlackHole* hole = new BlackHole(650, "BlackHole", "Purple", this);
	hole->setPosition(body->getPosition());
	setInitialVelocity(hole, 0.f);
	celestialBodies.push_back(hole); // Adăugăm noul Black Hole
	blackHoles.push_back(hole); // Adăugăm noul Black Hole în vectorul de Black Hole-uri
}
std::vector<sf::CircleShape> SolarSpace::createSpriteCelestialBody()
{
	std::vector<sf::CircleShape> sprites;
	for (auto body : celestialBodies) {
		sprites.push_back(createGlowSprite(body));
		sprites.push_back(createSpriteEntity(body));
		
	}
	for (auto body : asteroids) {
		sprites.push_back(createSpriteEntity(body));
	}

	return sprites;
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
void SolarSpace::updateCelestialBodiesGravity(float deltaTime) const
{
	for (auto body : celestialBodies) {
		sf::Vector2f totalAcceleration(0.f, 0.f);
		for (auto otherBody : celestialBodies)
			if (body != otherBody)
				totalAcceleration += computeGravity(otherBody, body);
			
		body->setVelocity(body->getVelocity() + totalAcceleration * deltaTime);
		body->setPosition(body->getPosition() + body->getVelocity() * deltaTime);	
	}
}

bool SolarSpace::checkColision(CelestialEntity* body1, CelestialEntity* body2)
{
	if (!body1 || !body2)
		return false;
	sf::Vector2f b1_pos = body1->getPosition();
	float error = 5.f;
	if (body1->getType() == "BlackHole" || body2->getType() == "BlackHole")
		error = 100.f;
	
	sf::Vector2f b2_pos = body2->getPosition();
	float distance = sqrt(pow(b1_pos.x - b2_pos.x, 2) + pow(b1_pos.y - b2_pos.y, 2));
	float rangeSize = body1->getSize() + body2->getSize() ;
	if (distance - error <= rangeSize)
		return true;
	return false;
}

void SolarSpace::setInitialVelocity(CelestialEntity* body, float speedMultiplier)
{
	CelestialEntity* StrongestBody = findStrongestEntity(body);
	if (body == StrongestBody) {
		body->setVelocity({ -20.f,-20.f });
		return;
	}
	sf::Vector2f direction = body->getPosition() - StrongestBody->getPosition();
	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	sf::Vector2f tangentVelocity(-direction.y, direction.x);
	body->setVelocity((tangentVelocity / distance) * speedMultiplier);
}
CelestialEntity* SolarSpace::findStrongestEntity(CelestialEntity* body) {
	CelestialEntity* closestEntity = nullptr;
	auto [x_body, y_body] = body->getPosition();
	float maxGravityPower = std::numeric_limits<float>::lowest(), generatedGravityPower;
	for (auto otherBody : celestialBodies)
		if (otherBody != body) {
			sf::Vector2f otherBodyPositions = otherBody->getPosition();
			float distance = sqrt(pow(x_body - otherBodyPositions.x, 2) + pow(y_body - otherBodyPositions.y, 2));
			if (distance <= 10.f)
				continue;
			generatedGravityPower = otherBody->getMass() / distance;
			if (generatedGravityPower > maxGravityPower)
			{
				maxGravityPower = generatedGravityPower;
				closestEntity = otherBody;
			}
		}
	if (closestEntity == nullptr)
		return body;
	return closestEntity;
}

sf::CircleShape SolarSpace::createSpriteEntity(CelestialEntity* entity) const
{
	static  float factorScale = 2.1;
	static  float growingRate = 0.02f;
		sf::CircleShape entitySprite(entity->getSize());
		entitySprite.setPosition(entity->getPosition());
		entitySprite.setOrigin(entitySprite.getGeometricCenter());
		if (entity->getType() == "Sun")
			entitySprite.setTexture(&sunTexture);
		else if (entity->getType() == "Planet")
			entitySprite.setTexture(&planetTexture);
		else if (entity->getType() == "BlackHole")
			entitySprite.setTexture(&blackHoleTexture);
		

		if (entity->getType() == "Sun") {
			
			if (factorScale >= 3.5)
				growingRate *= -1;
			else if (factorScale < 2) 
				growingRate *= -1;
			
			entitySprite.scale({ sqrt(factorScale),sqrt(factorScale)});
			factorScale += growingRate;
		}
		
		
		entitySprite.setFillColor(convertColor(entity->getColor()));
		
		return entitySprite;
	
}

sf::CircleShape SolarSpace::createGlowSprite(CelestialEntity* entity) const
{
	sf::CircleShape glowSprite(entity->getSize() * 2.0f,70); 
	glowSprite.setPosition(entity->getPosition());
	glowSprite.setOrigin(glowSprite.getGeometricCenter());
	glowSprite.setFillColor(convertColor(entity->getColor()));
	
	return glowSprite;
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
float SolarSpace::getRandomNumber(float lowerRange, float upperRange) const {
	static std::mt19937 rng(static_cast<unsigned>(time(nullptr)));
	std::uniform_real_distribution<float> dist(lowerRange, upperRange);
	return dist(rng);
}
void SolarSpace::createAsteroids(int number)
{
	for (int i = 0; i < number; i++) {
		float size = getRandomNumber(40.f, 70.f);
		Asteroid* asteroid = new Asteroid(size, "Asteroid" + std::to_string(i), "white", this);
		asteroid->setType("Asteroid");
		asteroid->setDamage(size * asteroid->getPower());
		float x = getRandomNumber(-80000,80000);
		float y = getRandomNumber(-80000, 80000);
		asteroid->setPosition({ x,y });
		asteroid->setVelocity({-x/300,-y/300});
		asteroids.push_back(asteroid);
	}
}
bool SolarSpace::entityOnHover(CelestialEntity* entity) {
	
	sf::Vector2f bodyPos = entity->getPosition();
	float distance = sqrt(pow(mousePos.x - bodyPos.x, 2) + pow(mousePos.y - bodyPos.y, 2));
	if (distance <= entity->getSize()*2)
		return true;
	return false;
}
sf::Color SolarSpace::convertColor(std::string color) const {
	std::transform(color.begin(), color.end(), color.begin(), ::tolower);

	if (color == "red")        return sf::Color::Red;
	if (color == "yellow")     return sf::Color::Yellow;
	if (color == "green")      return sf::Color::Green;
	if (color == "blue")       return sf::Color::Blue;
	if (color == "purple")     return sf::Color(128, 0, 128);
	if (color == "cyan")       return sf::Color::Cyan;
	if (color == "magenta")    return sf::Color::Magenta;
	if (color == "orange")     return sf::Color(255, 165, 0);
	if (color == "pink")       return sf::Color(255, 105, 180);
	if (color == "brown")      return sf::Color(165, 42, 42);
	if (color == "gray" || color == "grey") return sf::Color(128, 128, 128);
	if (color == "darkblue")   return sf::Color(0, 0, 139);
	if (color == "darkgreen")  return sf::Color(0, 100, 0);
	if (color == "gold")       return sf::Color(255, 215, 0);
	if (color == "silver")     return sf::Color(192, 192, 192);
	if (color == "white")      return sf::Color::White;
	if (color == "black")      return sf::Color::Black;
	return sf::Color::White;
}
sf::Text SolarSpace::entityOnHoverText(CelestialEntity* entityOnHover)
{
	sf::Text text(font);
	std::string message = "Entity: " + entityOnHover->getName();
	text.setCharacterSize(entityOnHover->getSize());
	text.setString(message);
	text.setPosition({ entityOnHover->getPosition().x - entityOnHover->getSize()*3, entityOnHover->getPosition().y + entityOnHover->getSize() * 2});
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	return text;
}
void SolarSpace::updateAsteroids() {
	for (auto asteroid : asteroids) {
		asteroid->setPosition(asteroid->getPosition() + asteroid->getVelocity());
		if (asteroid->getPosition().x > 100000 || asteroid->getPosition().x < -100000 ||
			asteroid->getPosition().y > 100000 || asteroid->getPosition().y < -100000) {
			asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), asteroid), asteroids.end());
			std::cout << "The asteroid " << asteroid->getName() << " was removed from the space" << std::endl;
		}
	}
}
void SolarSpace::updateAsteroidColision()
{
	for (CelestialEntity* entity : asteroids) {
	
		Asteroid* asteroid = dynamic_cast<Asteroid*>(entity);
		if (!asteroid)
			continue; 
		for (auto body : planets) {
			if (checkColision(asteroid, body)) {
				std::cout << "The asteroid " << asteroid->getName() << " hit the planet " << body->getName() << std::endl;
				body->setHealth(body->getHealth() - asteroid->getPower());
				if (body->getHealth() <= 0) {
					std::cout << "The planet " << body->getName() << " was destroyed by the asteroid " << asteroid->getName() << std::endl;
					celestialBodies.erase(std::remove(celestialBodies.begin(), celestialBodies.end(), body), celestialBodies.end());
					planets.erase(std::remove(planets.begin(), planets.end(), body), planets.end());
				}
				asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), asteroid), asteroids.end());
			}
			
		}
	}
	for (auto asteroid : asteroids) {
		for (auto body : celestialBodies) {
			if (checkColision(asteroid, body) && body->getType() != "Planet") {
				body->setSize(body->getSize() + asteroid->getSize());
				std::cout << "The asteroid " << asteroid->getName() << " hit the " << body->getName() << std::endl;
				celestialBodies.erase(std::remove(celestialBodies.begin(), celestialBodies.end(), asteroid), celestialBodies.end());
				asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), asteroid), asteroids.end());
			}
		}
	}
}
std::vector<sf::Text> SolarSpace::createTextEntity()
{
	std::vector<sf::Text> texts;
	for (auto body : celestialBodies) {
		if (entityOnHover(body)) {
			texts.push_back(entityOnHoverText(body));
		}
	}
	return texts;
}
sf::Vector2f SolarSpace::getHoverPos(sf::Vector2f defaultPosView) {
	for (auto body : celestialBodies)
		if (entityOnHover(body) && mousePressed)
			return body->getPosition();
	return defaultPosView;
}

void SolarSpace::clearSpace() {
	// Delete all objects in the celestialBodies vector
	for (auto body : suns) {
		if (body)
			delete body;
	}
	for (auto body : planets) {
		if (body)
			delete body;
	}
	for (auto body : asteroids) {
		if (body)
			delete body;
	}
	for (auto body : blackHoles) {
		if (body)
			delete body;
	}
	// Clear the vectors
	celestialBodies.clear();  // Clear the vector after deletion
	suns.clear();
	planets.clear();
	blackHoles.clear();
	asteroids.clear();

}
void SolarSpace::callAction(){
	updateCelestialBodiesGravity(0.15f);
	updateAsteroids();
	updateCelestialBodiesColision();
	updateAsteroidColision();
}

SolarSpace::~SolarSpace() {}