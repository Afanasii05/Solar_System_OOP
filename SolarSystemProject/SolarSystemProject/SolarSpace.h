/*
#pragma once
#include <vector>
#include <memory> 
#include <iostream>
#include "Sun.h"
#include "Planet.h"
class SolarSpace
{
private:
	int size_x;
	int size_y;
	float expansion_speed = 0.001;
	int Age=0;
	std::vector<std::shared_ptr<Sun>> suns;
	std::vector<std::shared_ptr<Planet>> planets;
	char name[30];
protected:
	const float GravitationalConstant = 6.67430e-11;
	
public:
	SolarSpace(int size_x, int size_y, char name[30]);
	void AddSun(std::shared_ptr<Sun> sun);
	void AddPlanet(std::shared_ptr<Planet> planet);
	~SolarSpace();

};
*/
