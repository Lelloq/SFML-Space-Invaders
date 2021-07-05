#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Alien.h"

sf::Sprite Alien::DrawAlien(int i, int j,int Anim)//Sprite swapping between sprite one sprite two for each alien
{
	if (Anim == 1)
	{
		if (i == 0) { Sprites[i][j].setTexture(TexA1); }//Top row uses InvaderA1.png
		else if (i == 1) { Sprites[i][j].setTexture(TexB1); }//Middle row uses InvaderB1.png
		else { Sprites[i][j].setTexture(TexC1); }//Bottom row uses InvaderC1.png
		return Sprites[i][j];
	}
	else if (Anim == 2);
	{
		if (i == 0) { Sprites[i][j].setTexture(TexA2); }//Top row uses InvaderA2.png
		else if (i == 1) { Sprites[i][j].setTexture(TexB2); }//Middle row uses InvaderB2.png
		else { Sprites[i][j].setTexture(TexC2); }//Bottom row uses InvaderC2.png
		return Sprites[i][j];
	}
}

void Alien::MoveAlien(float x, float y)//Moves each and every alien by an amount decided by those parameter values
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 10; j++) { Sprites[i][j].move(x,y); }
	}
}
sf::FloatRect Alien::GetHitBox(int i, int j)//Gets the hit box of the aliens
{
	return Sprites[i][j].getGlobalBounds();
}

sf::Sprite Alien::GetSprite(int i, int j)
{
	return Sprites[i][j];
}

void Alien::ResetPositions(int i, int j)//Resets the alien sprite positions back to a grid formation near the top of the screen
{
   Sprites[i][j].setPosition((j * 50.f) + 150.f, (i * 50.f) + 100.f);
}

void Alien::StoreAliens()
{
	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:
			for (int j = 0; j < 10; j++) 
			{
				Sprites[i][j] = ASprite1; //InvaderA images
				Sprites[i][j].setPosition((j * 50.f) + 150.f, (i * 50.f) + 100.f);//Set the positions to near the top of the screen in the middle
			}
			break;
		case 1:
			for (int j = 0; j < 10; j++) 
			{ 
				Sprites[i][j] = ASprite2; //InvaderB images
				Sprites[i][j].setPosition((j * 50.f) + 150.f, (i * 50.f) + 100.f);//Set the positions to near the top of the screen in the middle
			}
			break;
		case 2:
			for (int j = 0; j < 10; j++) 
			{
				Sprites[i][j] = ASprite3; //InvaderC images
				Sprites[i][j].setPosition((j * 50.f) + 150.f, (i * 50.f) + 100.f);//Set the positions to near the top of the screen in the middle
			}
			break;
		}

	}
}