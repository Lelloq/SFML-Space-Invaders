#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Ship.h"

sf::Sprite PlayerShip::DrawShip(int iState)
{
	switch (iState)//Returns the ship state
	{
	case 0:
		return Ship;
		break;
	case 1:
		return SCLeft;
		break;
	case 2:
		return SCRight;
		break;
	}
	return Ship;
}

float PlayerShip::GetSpeed()
{
	return fMoveSpeed;
}