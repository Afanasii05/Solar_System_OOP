#include "GameManager.h"
#include "SolarSpace.h"
#include <SFML/Window.hpp>
#include "CameraMovement.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>


sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t) {
    return start + (end - start) * t;
}

void GameManager::action(SolarSpace* space)
{
    CameraMovement camera;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width,height }), "windowView");
    sf::View view;
    view.setCenter({ 0.f, 0.f });
    view.setSize({ 19200.f, 10800.f });
    window->setFramerateLimit(60);
    window->setView(view);

    sf::Texture texture;
    if (!texture.loadFromFile("spaceTexture3.jpg"))
        std::cout << "Fail!";
    sf::Sprite background(texture);
    texture.setSmooth(true);

    sf::Vector2u windowSize = window->getSize();
    sf::Vector2u textureSize = texture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    background.setScale({ scaleX, scaleY });
    background.setPosition({ 0, 0 });

    float maxZoom = 10.f, minZoom = 0.5f, curentZoom = 1.f;
    sf::Vector2f mousePos, destination;
    destination = view.getCenter();

    sf::Clock deltaClock;
    bool transition = false;
    while (window->isOpen()) {
        float dt = deltaClock.restart().asSeconds();

        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();

            const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>();
            if (mouseWheelScrolled && mouseWheelScrolled->wheel == sf::Mouse::Wheel::Vertical) {
                if (mouseWheelScrolled->delta > 0 && curentZoom >= minZoom) {
                    view.zoom(0.95f);
                    curentZoom *= 0.95f;
                }
                else if (mouseWheelScrolled->delta < 0 && curentZoom <= maxZoom) {
                    view.zoom(1.05f);
                    curentZoom *= 1.05f;
                }
            }

            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
                    space->setMousePressed(true);
                    destination = space->getHoverPos(view.getCenter());
					if (destination != view.getCenter()) {
						transition = true;
					}
                }
            }
        }

        mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        space->SetMousePos(mousePos);

        const float smoothing = 5.f;
        sf::Vector2f currentCenter = view.getCenter();
        sf::Vector2f newCenter = lerp(currentCenter, destination, smoothing * dt);
        if (transition) {
            if (std::hypot(destination.x - newCenter.x, destination.y - newCenter.y) > 0.5f) {
                view.setCenter(newCenter);
            }
        }
           
        if (sqrt(pow(destination.x - newCenter.x, 2) + pow(destination.y - newCenter.y, 2)) < 40.f)
            transition = false;
        if (!transition) {
            view.move(camera.GetInput());
        }
        window->setView(view);

        space->callAction();

        window->clear();   //DRAWING --->>>>>>>>>>>>>>
        
        window->setView(window->getDefaultView());
        window->draw(background);

        // obiecte ceresti
        window->setView(view);
        for (sf::CircleShape celestialBody : space->createSpriteCelestialBody())
            window->draw(celestialBody);

        for (sf::Text text : space->createTextEntity())
            window->draw(text);
        if(gameTick%600==0)
			space->createAsteroids(10);
        window->display();



        space->setMousePressed(false);
        gameTick++;

    }
}
