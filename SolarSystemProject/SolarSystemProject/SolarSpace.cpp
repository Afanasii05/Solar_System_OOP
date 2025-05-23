#include "SolarSpace.h"
#include <cmath>
#include <ctime>
#include <random>
#include "Asteroid.h"
#include <iostream>
//Constructor SolarSpace neparametrizat, incarc Texturile
SolarSpace::SolarSpace() {
	
}
void SolarSpace::addCelBody(CelestialEntity* body) {
	celestialBodies.push_back(body); //adaug fiecare obiect de tip ClestialEntity (cu exceptia asteroizilor) in vectorul celestialBodies(drept pointeri)
}

void SolarSpace::updateCelestialBodiesColision() { //determin coliziunea intre obiecte
	for (size_t i = 0; i < celestialBodies.size(); ++i) {
		CelestialEntity* body1 = celestialBodies[i];
		if (!body1) continue;

		for (size_t j = 0; j < celestialBodies.size(); ) {
			CelestialEntity* body2 = celestialBodies[j];
			if (!body2 || body1 == body2) {//sa fie diferite
				++j;
				continue;
			}
			if (checkColision(body1, body2)) {//verific coliziunea
				if (body1->getMass() > body2->getMass()) {
					body1->setSize(body1->getSize() + body2->getSize());//obiectul cu masa mai mare se mareste in diametru
					celestialBodies.erase(celestialBodies.begin() + j);//sterg obiectul mai mic(l-a mancat)
					continue;
				}
			}

			++j;
		}

		if (body1->getSize() >= size_for_blackHole && body1->getType() != "BlackHole") {//daca un soare are dimenziunea necesara sa fie black-Hole
			updateSuntoBlackHole(body1);//creez blackHole
			celestialBodies.erase(celestialBodies.begin() + i);//sterg soarele
			i--;
			continue;
			
		}
	}
}

void SolarSpace::updateSuntoBlackHole(CelestialEntity* body) {//transform din soare in blackHole
	BlackHole* hole = new BlackHole(650, "BlackHole", "Purple", this);//creez obiectul
	hole->setPosition(body->getPosition());//ii ofer pozitia soarelui
	setInitialVelocity(hole, 0.f);//initialVelocity 0, sa nu zboare haotic prin spatiu
	celestialBodies.push_back(hole);//il bag in vector
}
std::vector<sf::CircleShape> SolarSpace::createSpriteCelestialBody()//creez obiectele vizual
{
	std::vector<sf::CircleShape> sprites;
	for (auto body : celestialBodies) {
		sprites.push_back(createGlowSprite(body));//un obiect mai mare decat cel ceresc, un fel de aura
		sprites.push_back(createSpriteEntity(body));//obiectul propriu-zis
		
	}
	for (auto body : asteroids) {//asteroizii la randul lor, dar nu ii bag in celestialBodies pentru ca sunt prea haotici
		sprites.push_back(createSpriteEntity(body));
	}
	return sprites;//returnez vectorul cu obiecte de desenat sa le desenez in GameManager
}

sf::Vector2f SolarSpace::computeGravity(CelestialEntity* body1, CelestialEntity* body2) const //calculez gravitatia dintre 2 obiecte
{
	auto [x_body2, y_body2] = body2->getPosition();//determin pozitiile celor 2 obiecte
	auto [x_body1, y_body1] = body1->getPosition();
	float distance = sqrt(pow(x_body2 - x_body1, 2) + pow(y_body2 - y_body1, 2)) + errorConstant;//calculez distanta dintre ele
	if (distance < 50.f) //in caz ca e prea mica gravitatia va fi 0 pentru a nu avea un comportament ciudat+ coliziunea deja e implementata, + evit impartirea la 0
		return { 0.f, 0.f };
	sf::Vector2f direction = { x_body1-x_body2, y_body1 - y_body2};//directia vectoriala , pentru a seta "velocitatea" gravitatiei de la un corp la celalat
	direction /= distance;//normalizez 
	float force = GravitationalConstant * (body1->getMass()) / (distance * distance);//formula gravitatiei
	sf::Vector2f acceleration =  direction * force;//determin acceleratia cu care trebuie sa se duca corpul 2 catre corpul 1
	return acceleration;//returnez acest vector de acceleratie cu 2 componente  (deoarece e 2D simularea)
}
void SolarSpace::updateCelestialBodiesGravity(float deltaTime) const//determin gravitatia intre toate obiectele
{
	for (auto body : celestialBodies) {
		sf::Vector2f totalAcceleration(0.f, 0.f);//vectorul de acceleratie pentru fiecare obiect
		for (auto otherBody : celestialBodies)
			if (body != otherBody)//evit gravitatia intre acelasi obiect
				totalAcceleration += computeGravity(otherBody, body);//apelez functia pentru a determina gravitatia cu formula gravitatiei
			
		body->setVelocity(body->getVelocity() + totalAcceleration * deltaTime);//tranzitie smooth 
		body->setPosition(body->getPosition() + body->getVelocity() * deltaTime);//actualizez pozitia in functie de velocity si deltaTime
	}
}

bool SolarSpace::checkColision(CelestialEntity* body1, CelestialEntity* body2)//functia de coliziune in cazul 2 corpuri au puncte comune in spatiu
{
	if (!body1 || !body2)//daca unul din ele e nullptr -> return false(evit segment fault)
		return false;
	sf::Vector2f b1_pos = body1->getPosition();
	float error = 5.f;//chiar daca nu sunt exact unul in celalalt
	if (body1->getType() == "BlackHole" || body2->getType() == "BlackHole")
		error = 100.f;//in cazul in care e BlackHole maresc aceasta destanta error
	
	sf::Vector2f b2_pos = body2->getPosition();
	float distance = sqrt(pow(b1_pos.x - b2_pos.x, 2) + pow(b1_pos.y - b2_pos.y, 2));//distanta 
	float rangeSize = body1->getSize() + body2->getSize();
	if (distance - error <= rangeSize)//coliziune intre cercuri ,lungimea razelor adunate mai mare decat distanta dintre ele 
		return true;
	return false;
}

void SolarSpace::setInitialVelocity(CelestialEntity* body, float speedMultiplier)//velocity initial, exact ca in viata reala,
																				//corpurile ceresti au o un velocity, din acest motiv planeta nu este atrasa direct in soare
																				//planeta este afectata de gravitatia soarelui dar reuseste sa evite impactul prin viteza initiala pe care deja o are			
{
	CelestialEntity* StrongestBody = findStrongestEntity(body);// ii dau un initialVelocity in functie de opiectul cu cel mai mare camp gravitational in functie de corpul actual
	if (body == StrongestBody) {
		body->setVelocity({ -20.f,-20.f });//daca acesta e insasi el(nu a gasit un alt corp), ii dau un velocity spre colt stanga sus(e random, nu conteaza in cazul asta)
		return;
	}
	sf::Vector2f direction = body->getPosition() - StrongestBody->getPosition();//determin directia corpul actual si corpul cu cel mai puternic camp gravitational, vectori simpli
	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);//distanta dintre ele
	sf::Vector2f tangentVelocity(-direction.y, direction.x);//ii dau directia la 90 de grade fata de StrongestBody, ca sa se duca in sens de orbita ci nu sa fuga de el sau sa se duca in el
	body->setVelocity((tangentVelocity / distance) * speedMultiplier);//actualizez velocity in functie de distanta si o variabila de viteza
}
CelestialEntity* SolarSpace::findStrongestEntity(CelestialEntity* body) {//functia de a gasi obiectul cu cea mai mare forta gravitationala in functie de un anumit corp
	CelestialEntity* closestEntity = nullptr;//over o valoare nula
	auto [x_body, y_body] = body->getPosition();//coordonatele body
	float maxGravityPower = std::numeric_limits<float>::lowest(), generatedGravityPower;
	for (auto otherBody : celestialBodies)//o functie de a determina max
		if (otherBody != body) {
			sf::Vector2f otherBodyPositions = otherBody->getPosition();
			float distance = sqrt(pow(x_body - otherBodyPositions.x, 2) + pow(y_body - otherBodyPositions.y, 2));
			if (distance <= 10.f)//nu iau in calcul obiecte foarte foarte apropiate
				continue;
			generatedGravityPower = otherBody->getMass() / distance;//o formula simpla de gravitatie
			if (generatedGravityPower > maxGravityPower)
			{
				maxGravityPower = generatedGravityPower;
				closestEntity = otherBody;
			}
		}
	if (closestEntity == nullptr)//daca nu s a gasit niciun obiect, returnez acelasi corp
		return body;
	return closestEntity;
}

sf::CircleShape SolarSpace::createSpriteEntity(CelestialEntity* entity) const//creez obiectul in mod vizual pentru a il baga intr-un vector de Shapes 
{
     float factorScale = 2.1;
	 float growingRate = 0.02f;//variabile pt "grow" al soarelui
		sf::CircleShape entitySprite(entity->getSize());//creez un obiect de tip circleSHape si ii ofer marimea obiectului
		entitySprite.setPosition(entity->getPosition());//setez pozitia
		entitySprite.setOrigin(entitySprite.getGeometricCenter());
		if (entity->getType() == "Sun")//implementez textura
			entitySprite.setTexture(mng.getsunTexture());
		else if (entity->getType() == "Planet")
			entitySprite.setTexture(mng.getplanetTexture());
		else if (entity->getType() == "BlackHole")
			entitySprite.setTexture(mng.getblackHoleTexture());
		

		if (entity->getType() == "Sun") {//"animatie" de grow
			
			if (factorScale >= 3.5)
				growingRate *= -1;
			else if (factorScale < 2) 
				growingRate *= -1;
			
			entitySprite.scale({ sqrt(factorScale),sqrt(factorScale)});
			factorScale += growingRate;
		}
		
		
		entitySprite.setFillColor(convertColor(entity->getColor()));//culoarea 
		
		return entitySprite;//returnez spriteul 
	
}

sf::CircleShape SolarSpace::createGlowSprite(CelestialEntity* entity) const//creez un sprite langa cel original, unul mai mare pentru a da efect de glow
{
	sf::CircleShape glowSprite(entity->getSize() * 2.0f,70); //maresc diametrul
	glowSprite.setPosition(entity->getPosition());
	glowSprite.setOrigin(glowSprite.getGeometricCenter());
	glowSprite.setFillColor(convertColor(entity->getColor()));
	return glowSprite;
}


float SolarSpace::getRandomNumber(float lowerRange, float upperRange) const {//functie de random number
	static std::mt19937 rng(static_cast<unsigned>(time(nullptr)));
	std::uniform_real_distribution<float> dist(lowerRange, upperRange);
	return dist(rng);
}
void SolarSpace::createAsteroids(int number)//creez asteroizii care se genereaza dinamic pe parcurs
{
	for (int i = 0; i < number; i++) {
		float size = getRandomNumber(40.f, 70.f);//sa nu aiba toti aceeasi mairime
		Asteroid* asteroid = new Asteroid(size, "Asteroid" + std::to_string(i), "white");
		asteroid->setType("Asteroid");
		asteroid->setDamage(size * asteroid->getPower());
		float x = getRandomNumber(-80000,80000);//generez random prin spatiu
		float y = getRandomNumber(-80000, 80000);
		asteroid->setPosition({ x,y });
		asteroid->setVelocity({-x/300,-y/300});//ii pun sa se duca catre centru
		asteroids.push_back(asteroid);//ii bag in vectorul de asteroizi si nu in cel de celestialbodies
	}
}
bool SolarSpace::entityOnHover(CelestialEntity* entity) {//returnez daca tin hover pe unul din obiectele ceresti inafara de asteroizi
	
	sf::Vector2f bodyPos = entity->getPosition();
	float distance = sqrt(pow(mousePos.x - bodyPos.x, 2) + pow(mousePos.y - bodyPos.y, 2));
	if (distance <= entity->getSize()*2)
		return true;
	return false;
}
sf::Color SolarSpace::convertColor(std::string color) const {//convertesc din string in sf::Color
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
sf::Text SolarSpace::entityOnHoverText(CelestialEntity* entityOnHover)//returnez textul in functie de obiectul pe care am hover la mouse
{
	sf::Text text(*mng.getFont());
	std::string message = "Entity: " + entityOnHover->getName();
	text.setCharacterSize(entityOnHover->getSize());
	text.setString(message);
	text.setPosition({ entityOnHover->getPosition().x - entityOnHover->getSize()*3, entityOnHover->getPosition().y + entityOnHover->getSize() * 2});//setez textul sub pozitia obiectului
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	return text;
}
void SolarSpace::updateAsteroids() {//logica pt asteroizi
	for (auto asteroid : asteroids) {
		asteroid->setPosition(asteroid->getPosition() + asteroid->getVelocity());//tranzitie de mers prin spatiu
		if (asteroid->getPosition().x > 100000 || asteroid->getPosition().x < -100000 ||
			asteroid->getPosition().y > 100000 || asteroid->getPosition().y < -100000) { //in cazul in care trec de anumite limite ale spatiului ii sterg
			asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), asteroid), asteroids.end());
			std::cout << "The asteroid " << asteroid->getName() << " was removed from the space" << std::endl;
		}
	}
}
void SolarSpace::updateAsteroidColision()//logica de coliziune a asteroizilor
{
	for (Asteroid* entity : asteroids) {
		if (!entity)//evit daca e vreo sansa sa fie nullptr
			continue; 
		for (auto body : celestialBodies) {
			if (dynamic_cast<Planet*>(body)) {//vad daca e  planeta (logica de lovire a planetelor)
				Planet* planet = static_cast<Planet*>(body); //stiu ca e planeta, convertesc la ea sa pot apela functiile de getHealth
				if (checkColision(entity, body)) { //daca exista coliziune planeta pierde din viata
					std::cout << "The asteroid " << entity->getName() << " hit the planet " << body->getName() << std::endl;
					planet->setHealth(planet->getHealth() - entity->getPower());
					if (planet->getHealth() <= 0) {//in cazul in care health<=0 planeta este distrusa si stearsa
						std::cout << "The planet " << body->getName() << " was destroyed by the asteroid " << entity->getName() << std::endl;
						celestialBodies.erase(std::remove(celestialBodies.begin(), celestialBodies.end(), body), celestialBodies.end());
					}
					asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), entity), asteroids.end());
				}
			}
			
		}
	}
	for (auto asteroid : asteroids) {//in cazul in care se loveste de BlackHole sau Sun, e inghitit
		for (auto body : celestialBodies) {
			if (checkColision(asteroid, body) && body->getType() != "Planet") {//evit planetele
				body->setSize(body->getSize() + asteroid->getSize());
				std::cout << "The asteroid " << asteroid->getName() << " hit the " << body->getName() << std::endl;
				celestialBodies.erase(std::remove(celestialBodies.begin(), celestialBodies.end(), asteroid), celestialBodies.end());
				asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), asteroid), asteroids.end());//sterg asteroidul care s a lovit
			}
		}
	}
}
sf::Text SolarSpace::createTextEntity()//returnez mesajul in functie de hover pt a i-l desena
{
	sf::Text text(*mng.getFont());
	for (auto body : celestialBodies) {
		if (entityOnHover(body)) {
			return entityOnHoverText(body);
		}
	}
	return text;
}
sf::Vector2f SolarSpace::getHoverPos(sf::Vector2f defaultPosView) {//returnez pozitia unui obiect din celestialBodies daca am dat click pe el, pt tranzitia de  la un obiect la altul prin click
	for (auto body : celestialBodies)
		if (entityOnHover(body) && mousePressed)
			return body->getPosition();
	return defaultPosView;
}

void SolarSpace::clearSpace() {
	// Delete all objects in the celestialBodies vector
	
	for (auto body : asteroids) {
		if (body)
			delete body;
	}
	for (auto body : celestialBodies) {
		if (body)
			delete body;
	}
	// Clear the vectors
	celestialBodies.clear();  // Clear the vector after deletion
	asteroids.clear();

}
void SolarSpace::callAction(){//apelez functiile necesare pt ca spatiul sa functioneze, acesta este chemat intr-un gameManager
	updateCelestialBodiesGravity(0.15f);
	updateAsteroids();
	updateCelestialBodiesColision();
	updateAsteroidColision();
}

SolarSpace::~SolarSpace() {}