
#include "SolarSpace.h"
#include "Sun.h"
SolarSpace::SolarSpace(int size_x, int size_y)
{
	this->size_x = size_x;
	this->size_y = size_y;
	vectSpace.resize(size_x);
	for (int i = 0; i < size_x; ++i) 
		vectSpace[i].resize(size_y);
}

void SolarSpace::addSun(int positions[2],int size)
{
	int pos_x = size_x / 2 + positions[0]-size;
	int pos_y = size_y / 2 + positions[1]-size;
	int end_x = pos_x + 2 * size + 1;
	int end_y = pos_y + 2 * size + 1;
	
	

	if(checkPositions(pos_x,pos_y,end_x,end_y,size))
		for (int row = pos_x;row < end_x;row++)
			for (int col = pos_y;col < end_y;col++)
				vectSpace[row][col] = 1;
	else
		std::cout << "There is not enough space for the sun\n";
	
	
}
bool SolarSpace::checkPositions(int pos_x,int pos_y,int end_x,int end_y, int size)
{
	for (int row = pos_x;row < end_x;row++)
		for (int col = pos_y;col < end_y;col++)
			if (vectSpace[row][col] != 0)
				return false;
	return true;

}
void SolarSpace::display() {
	for (short iterator = 0;iterator < size_x;iterator++)
	{
		for (short iterator2 = 0; iterator2 < size_y; iterator2++)
			std::cout << vectSpace[iterator][iterator2]<<' ';
		std::cout << '\n';
	}
}
SolarSpace::~SolarSpace() {};