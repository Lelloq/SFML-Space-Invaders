#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
private:
	sf::Sprite BulletSprite;
	sf::Texture BulletTexture;
public:
	Bullet()
	{
		if (BulletTexture.loadFromFile(".\\assets\\images\\Bullet.png")) BulletSprite.setTexture(BulletTexture);
	}

	sf::Sprite ShootBullet(float ix, float iy);
};