#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class Alien
{
private:
	sf::Sprite Sprites[3][10];
	sf::Sprite ASprite1, ASprite2, ASprite3;
	sf::Texture TexA1, TexA2, TexB1, TexB2, TexC1, TexC2;
	sf::FloatRect HitBox;
	int HP, MoveSpeed;
public:
	Alien()
	{
		if (TexA1.loadFromFile(".\\assets\\images\\InvaderA1.png"));
		if (TexA2.loadFromFile(".\\assets\\images\\InvaderA2.png"));
		if (TexB1.loadFromFile(".\\assets\\images\\InvaderB1.png"));
		if (TexB2.loadFromFile(".\\assets\\images\\InvaderB2.png"));
		if (TexC1.loadFromFile(".\\assets\\images\\InvaderC1.png"));
		if (TexC2.loadFromFile(".\\assets\\images\\InvaderC2.png"));
		MoveSpeed = 2;
	}
	sf::Sprite DrawAlien(int i, int j, int Anim);
	sf::FloatRect GetHitBox(int i, int j);
	sf::Sprite GetSprite(int i, int j);
	void MoveAlien(float x, float y);
	void ResetPositions(int i, int j);
	void StoreAliens();
};