#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

class Inputs
{
private:
	sf::Keyboard::Key Left;
	sf::Keyboard::Key Right;
	sf::Keyboard::Key Shoot;
public:
	Inputs()
	{
		Left = sf::Keyboard::Left;
		Right = sf::Keyboard::Right;
		Shoot = sf::Keyboard::Space;
	}
public:
	sf::Keyboard::Key getleft();
	sf::Keyboard::Key getright();
	sf::Keyboard::Key getshoot();
	sf::Keyboard::Key rebind(string Key, enum sf::Keyboard::Key Keycode);
};