#include <iostream>
#include "CelestialEntity.h"
#include "Sun.h"
#include "CameraMovement.h"
#include "Planet.h"
#include "SolarSpace.h"
#include <chrono>
#include <thread>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>

int main()
{
	const double timestep = 0.1;
	float p1[2] = {0,0};
	float p2[2] = { 320,180 };
	float p3[2] = { 700,320 };
	
	SolarSpace space;

	Sun* newsun= new Sun(110, p1, 0, 900, "yellow", "Marinica");
	
	Planet* newplanet = new Planet(15, p2, 0, true, "Marinica", 100);
	Planet* newplanet2 = new Planet(30, p3, 0, true, "Marinica2", 100);
	
	CameraMovement camera;
    std::vector<CelestialEntity*> entities;
	entities.push_back(newsun);
	entities.push_back(newplanet);
	space.findClosestEntity();

	space.setInitialVelocity(newplanet, 10.0f);
	space.setInitialVelocity(newplanet2, 17.0f);
	unsigned int width = 640,height=360;
	float deltaTime = 0.1f;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width,height }), "CACA");
	sf::View view;
	view.setCenter({ 320.f, 180.f });
	view.setSize({ 640.f, 360.f });
	window->setFramerateLimit(60);
	window->setView(view);
	while (window->isOpen()) {
		
		while (const std::optional event = window->pollEvent()) {
			if (event->is < sf::Event::Closed>()) {
				window->close();
			}
			const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>();
			if ( mouseWheelScrolled && mouseWheelScrolled->wheel == sf::Mouse::Wheel::Vertical) // check if the event is a mouse wheel scrolled event
					if (mouseWheelScrolled->delta> 0)
						view.zoom(0.95f);  // Zoom in
					else
						view.zoom(1.15f);  // Zoom out

					window->setView(view);
			
		}
		view.move(camera.GetInput());
		window->setView(view);
		space.updatePlanets(deltaTime);
		window->clear();
		for (sf::CircleShape sp : space.createSpriteSun()) {
			window->draw(sp);
		}
		for (sf::CircleShape sp : space.createSpritePlanets()) {
			window->draw(sp);
		}
		
		window->display();

	}
	for (auto obj : entities) {
		delete obj;
	}

	return 0;
}