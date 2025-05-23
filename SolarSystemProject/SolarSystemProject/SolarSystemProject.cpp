
//headers includes
#include "SolarSpace.h"
#include "GameManager.h"
#include "SystemGenerator.h"
//sfml includes


int main()
{
	
	SolarSpace space;//creez static un spatiu
	SystemGenerator MilkyWay({0,0},10,&space); //creez static prima galaxie
	SystemGenerator Andromeda({MilkyWay.getNextMinimumSunPos()*3,MilkyWay.getNextMinimumSunPos()}, 10, &space);//a doua galaxie pozitionata la o distanta anumita in functie de cea mai indepartata planeta a primei galaxii
	SystemGenerator Triangulum({ -1 * MilkyWay.getNextMinimumSunPos() * 3,0.f }, 10, &space);//o spawnez in partea inversa de prima galaxie
	SystemGenerator Gundenberg({Andromeda.getNextMinimumSunPos() * 3,0.f }, 10, &space);
	SystemGenerator Gundenberg2({ Triangulum.getNextMinimumSunPos() * 3,0.f }, 10, &space);
	GameManager manager;//creez menagerul ca sa pot rula simularea
	manager.action(&space);//apelez functia de action asupra spatiului creat, managerul ruleaza logica in functie de spatiul dat, care la randul lui 
						   //are stele planete asteroizi si gauriNegre
	space.clearSpace();//curat spatiul, sterg obiectele dinamice, nu il apelez in distructor deoarece vreau sa pot sa le sterg oricand vreau eu.
	return 0;
}