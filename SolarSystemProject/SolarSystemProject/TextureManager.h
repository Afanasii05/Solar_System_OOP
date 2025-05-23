#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>


class TextureManager
{  
	sf::Font font;
	sf::Texture sunTexture, blackHoleTexture, planetTexture;
public:
	TextureManager();
	sf::Font* getFont() { return &font; }
	const sf::Texture* getsunTexture() const { return &sunTexture; }
	const sf::Texture* getplanetTexture() const { return &planetTexture; }
	const sf::Texture* getblackHoleTexture() const { return &blackHoleTexture; }

};

