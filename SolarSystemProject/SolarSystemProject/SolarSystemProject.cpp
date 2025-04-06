
//headers includes
#include "SolarSpace.h"
#include "GameManager.h"
#include "SystemGenerator.h"
//sfml includes


int main()
{
	
	SolarSpace space;
	SystemGenerator MilkyWay({0,0},10,&space);
	SystemGenerator Andromeda({MilkyWay.getNextMinimumSunPos()*3,MilkyWay.getNextMinimumSunPos()}, 10, &space);
	SystemGenerator Triangulum({ -1 * MilkyWay.getNextMinimumSunPos() * 3,0.f }, 10, &space);
	
	GameManager manager;
	manager.action(&space);
	space.clearSpace();
	return 0;
}