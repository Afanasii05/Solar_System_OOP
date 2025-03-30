#include <iostream>
#include <vector>
//headers includes
#include "CameraMovement.h"
#include "Sun.h"
#include "SolarSpace.h"
//sfml includes
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

int main()
{
	const double timestep = 0.1;
	const unsigned int width = 1920, height = 1080;
	const float deltaTime = 0.1f;
	//Creez window SFML (rendering the objects in space)
	
	CameraMovement camera;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width,height }), "windowView");
	sf::View view; //Setarile pt view
	view.setCenter({ 960.f, 540.f });
	view.setSize({ 1920.f, 1080.f });
	window->setFramerateLimit(60);
	window->setView(view);

	
	
	SolarSpace space;
	Sun* sun1 = new Sun(140, 1000000, "Soare1");
	Sun* sun2 = new Sun(160, 1000000, "Soare2");

	Planet* planet1 = new Planet(30, true, "Earth", 1);
	Planet* planet2 = new Planet(50, true, "Marte", 1);

	planet1->setPosition({ 5200.f,1900.f });
	planet2->setPosition({ 3200.f , 1000.f });

	space.addSun(sun1);
	space.addSun(sun2);
	space.addPlanet(planet2);
	space.addPlanet(planet1);
	space.setInitialVelocity(planet1, 100.f);
	space.setInitialVelocity(planet2, 100.f);
	space.setInitialVelocity(sun1, 20.f);
	space.setInitialVelocity(sun2, 130.f);

	
	
	//Game loop unde are loc apelarea functiilor de logica din cadrul SolarSpace
	while (window->isOpen()) {
		
		while (const std::optional event = window->pollEvent()) {
			if (event->is < sf::Event::Closed>()) { //verific daca am apasat sa inchid window
				window->close();
			}
			const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>();
			if ( mouseWheelScrolled && mouseWheelScrolled->wheel == sf::Mouse::Wheel::Vertical) //verific daca eventul e mousescroll
					if (mouseWheelScrolled->delta> 0) //in functie de valoarea lui delta din cadrul mousewheelscrolled , vad daca e zoom in sau zoom out
						view.zoom(0.95f);  // Zoom in
					else
						view.zoom(1.15f);  // Zoom out

					window->setView(view);
			
		}
		view.move(camera.GetInput()); //in functie de tasta up down left right , mut camera
		window->setView(view);
		space.updatePlanets(deltaTime);	//updatez in gameloop pozitia planetelor  si a stelelor
		window->clear(); //are loc curatarea paginii inainte sa fie desenat din nou pe ecran
		for (sf::CircleShape sun : space.createSpriteSun())
			window->draw(sun);
		for (sf::CircleShape planet : space.createSpritePlanets())
			window->draw(planet);
		window->display(); //Afisez in window ce am desenat

	}

	delete sun1;
	return 0;
}