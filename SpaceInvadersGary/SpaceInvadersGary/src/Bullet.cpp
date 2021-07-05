#include "Bullet.h"
#include <SFML/Graphics.hpp>

sf::Sprite Bullet::ShootBullet(float fx, float fy)
{
	BulletSprite.setPosition(fx, fy);
	return BulletSprite;
}