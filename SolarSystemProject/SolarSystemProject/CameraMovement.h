#pragma once
#include <vector>
#include <SFML/System.hpp>
class CameraMovement
{
public:
	CameraMovement() {};
	~CameraMovement() {};
	sf::Vector2f GetInput();
	
};

