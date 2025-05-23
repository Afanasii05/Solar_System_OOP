#include "TextureManager.h"
#include <iostream>

TextureManager::TextureManager() {//incarc texturile
	if (!sunTexture.loadFromFile("sunTexture.png"))
		std::cout << "Fail!\n";
	sunTexture.setSmooth(true);
	if (!blackHoleTexture.loadFromFile("blackHoleTexture.jpg"))
		std::cout << "Fail!\n";
	blackHoleTexture.setSmooth(true);
	if (!planetTexture.loadFromFile("planetTexture.jpg"))
		std::cout << "Fail!\n";
	planetTexture.setSmooth(true);
	if (!font.openFromFile("arial.ttf"))
		std::cout << "Failed to load font\n";
}