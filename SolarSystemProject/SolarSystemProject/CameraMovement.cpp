#include "CameraMovement.h"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

sf::Vector2f CameraMovement::GetInput()
{
    float speed = 105.f; // Adjust speed as needed

    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        movement.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        movement.x += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        movement.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        movement.y += speed;

    return movement;
}
