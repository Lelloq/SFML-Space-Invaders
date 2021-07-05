#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class PlayerShip
{
private:
	sf::Texture ShipImage, SCLImage, SCRImage;
	sf::Sprite Ship, SCLeft, SCRight;
	float fMoveSpeed;
public:
	PlayerShip()
	{
		if (ShipImage.loadFromFile(".\\assets\\images\\Ship.png")) Ship.setTexture(ShipImage);
		if (SCLImage.loadFromFile(".\\assets\\images\\ShipCrushedLeft.png")) SCLeft.setTexture(SCLImage);
		if (SCRImage.loadFromFile(".\\assets\\images\\ShipCrushedRight.png")) SCRight.setTexture(SCRImage);
		fMoveSpeed = 5;
	}
	float GetSpeed();
	sf::Sprite DrawShip(int iState);
};