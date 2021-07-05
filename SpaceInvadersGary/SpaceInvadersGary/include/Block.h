#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class Block
{
private:
	sf::Texture FBImage, OKBImage, WBImage;
	sf::Sprite FBlock, OKBlock, WBlock;
public:
	Block()
	{
		if (FBImage.loadFromFile(".\\assets\\images\\FullBlock.png")) FBlock.setTexture(FBImage);
		if (OKBImage.loadFromFile(".\\assets\\images\\OkBlock.png")) OKBlock.setTexture(OKBImage);
		if (WBImage.loadFromFile(".\\assets\\images\\WeakBlock.png")) WBlock.setTexture(WBImage);
	}
	sf::Sprite DrawBlock(int iState);
};