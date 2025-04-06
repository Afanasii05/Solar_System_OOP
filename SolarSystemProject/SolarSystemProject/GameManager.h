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
	int frame_rate = 60;
	float gameSpeed = 100,speed=0.1;
	const  double timestep = 0.1;
	unsigned int gameTick = 0;
	const  unsigned int width = 1920, height = 1080;

	
public:
	void action(SolarSpace* space);

};

