
#pragma once
#include <vector>
#include <iostream>

class SolarSpace
{
private:
	int size_x;
	int size_y;
	std::vector<std::vector<short>> vectSpace;
protected:
	const float GravitationalConstant = 6.67430e-11;
	
	
public:
	SolarSpace(int size_x, int size_y);
	void display();
	bool checkPositions(int pos_x,int pos_y,int end_x,int end_y, int size);
	void addSun(int positions[2],int size);
	~SolarSpace();


};

