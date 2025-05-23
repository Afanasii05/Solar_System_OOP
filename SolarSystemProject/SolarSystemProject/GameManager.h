#pragma once
#include "GameManager.h"
#include "SolarSpace.h"
#include <SFML/Window.hpp>
#include "CameraMovement.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

class SolarSpace;
class GameManager
{
private:
	int frame_rate = 60; //frame-uri pe secunda
	
	unsigned int gameTick = 0; //Tick pt spawn al asteroizilor
	static const  unsigned int width = 1920, height = 1080; // marimea ferestrei

	
public:
	void action(SolarSpace* space); // game - loop, afiseaza un SolarSpace

};

