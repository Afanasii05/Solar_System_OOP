#pragma once
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class CameraMovement
{
	float maxZoom = 10.f, minZoom = 0.5f, curentZoom = 1.f;//valorile de minZoom si maxZoom 
	float speed = 105.f; //Viteza de deplasare
public:
	CameraMovement() {};
	~CameraMovement() {};
	void updateZoom(sf::View* view, const  sf::Event ev);
	sf::Vector2f GetInput();
	
};

