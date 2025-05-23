#include "CameraMovement.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

void CameraMovement::updateZoom(sf::View* view,const sf::Event ev)//Functie de zoom
{
    const auto* mouseWheelScrolled = ev.getIf<sf::Event::MouseWheelScrolled>();//in cazul in care eventul e de tip zoom
    if (mouseWheelScrolled && mouseWheelScrolled->wheel == sf::Mouse::Wheel::Vertical) {//actiune asupra rotitei
        if (mouseWheelScrolled->delta > 0 && curentZoom >= minZoom) {//zoom intre max si min zoom (limitez cat de mult pot da zoom)
            view->zoom(0.95f);
            curentZoom *= 0.95f;//micsorez curentZoom
        }
        else if (mouseWheelScrolled->delta < 0 && curentZoom <= maxZoom) {
            view->zoom(1.05f);
            curentZoom *= 1.05f;//maresc currentZoom
        }
    }
}

sf::Vector2f CameraMovement::GetInput()//Pt a putea deplasa cadrul standa dreapta sus jos
{
  
    sf::Vector2f movement(0.f, 0.f);
    //in cazul in care una dintre taste este apasata updatez vectorul de movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        movement.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        movement.x += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        movement.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        movement.y += speed;

    return movement;//returnez vectorul pentru a actualiza pozitia camerei
}
