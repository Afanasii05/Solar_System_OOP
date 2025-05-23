#include "GameManager.h"
#include "SolarSpace.h"
#include <SFML/Window.hpp>
#include "CameraMovement.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>

//Functie de tranzitie cand dai click pe un CelestialEntity
sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t) {
    return start + (end - start) * t;
}

void GameManager::action(SolarSpace* space)
{
    CameraMovement camera; // Creez un obiect de tip CameraMovement pentru a putea misca camera in toate directiile
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width,height }), "windowView"); //Fereastra din sfml
    sf::View view;//actualizez distanta in functie de zoom in zoom out
    view.setCenter({ 0.f, 0.f });
    view.setSize({ 19200.f, 10800.f });
    window->setFramerateLimit(60);
    window->setView(view);   //pun view in centrul window (initial zoom 1)

    sf::Texture texture;  //Setez imagine de background
    if (!texture.loadFromFile("spaceTexture3.jpg"))
        std::cout << "Fail!";
    sf::Sprite background(texture);
    texture.setSmooth(true);

    sf::Vector2u windowSize = window->getSize(); //Calculez cat trebuie sa mai maresc/micsorez imaginea de background pentru a acoperi toata fereastra
    sf::Vector2u textureSize = texture.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    background.setScale({ scaleX, scaleY });
    background.setPosition({ 0, 0 });

    sf::Vector2f mousePos, destination; //pt logica de click to view
    destination = view.getCenter();

    sf::Clock deltaClock;//clock pt tranzitie in functie de calculator
    bool transition = false;
    while (window->isOpen()) {
        float dt = deltaClock.restart().asSeconds();
        while (const std::optional event = window->pollEvent()) {//event de close window 
            if (event->is<sf::Event::Closed>())
                window->close();

            camera.updateZoom(&view, *event);//apel de zoom la camera
            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) //in caz ca apas click 
                if (mouseButtonPressed->button == sf::Mouse::Button::Left) {//doar pt click stanga
                    space->setMousePressed(true);
                    destination = space->getHoverPos(view.getCenter());//destinatia pt click (doar in caz ca e celestialEntity)
					if (destination != view.getCenter()) 
						transition = true;			//tranzitia catre acel obiect
                }
        }

        mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));//coordonatele pozitiei mouse
        space->SetMousePos(mousePos);
        sf::Vector2f newCenter = lerp(view.getCenter(), destination,5.f * dt);//catre noua pozitie
        if (transition&&std::hypot(destination.x - newCenter.x, destination.y - newCenter.y) > 0.5f)//cat timp tranzitia=true si distanta dintre noua pozitie si pozitia actuala >0.5  
               view.setCenter(newCenter);
        else
            transition = false;
        if (!transition)  //in cazul in care nu plec catre un nou view , pot sa me misc stanga dreapta sus jos
            view.move(camera.GetInput());

        window->setView(view); // actualizez view la window
        space->callAction(); // apelez functiile de logica din space

        window->clear();   //DRAWING --->>>>>>>>>>>>>>
        window->setView(window->getDefaultView());//pt background static
        window->draw(background);
        // obiecte ceresti
        window->setView(view);
        for (sf::CircleShape celestialBody : space->createSpriteCelestialBody())//desenez obiectele din spatiu
            window->draw(celestialBody);
        //in cazul in care am hover pe un celestialEntity sa afisez numele lui
            window->draw(space->createTextEntity());
        if(gameTick%600==0) // la fiecare 600 gameTick spawnezi asteroizi
			space->createAsteroids(10);
        window->display();

        space->setMousePressed(false);
        gameTick++; // cresc gameTick la fiecare loop

    }
}
