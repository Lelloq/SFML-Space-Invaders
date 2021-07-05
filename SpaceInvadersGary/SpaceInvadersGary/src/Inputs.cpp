#include <Inputs.h>
#include <SFML\Graphics.hpp>
#include <string>

sf::Keyboard::Key Inputs::getleft()
{
	return Left;
}
sf::Keyboard::Key Inputs::getright()
{
	return Right;
}
sf::Keyboard::Key Inputs::getshoot()
{
	return Shoot;
}
sf::Keyboard::Key Inputs::rebind(string Key, enum sf::Keyboard::Key Keycode)
{
	sf::Keyboard::Key NewInput;
	for (int i = 0; i < 101; i++)//iterates through all the sfml keycodes and checks if its the same as the parameter Keycode if it is then it will change the NewInput variable to that
	{
		if (Keycode == i)
		{
			NewInput = Keycode;
		}
	}
	if (Key == "Left")//if it is the left button it will change the new input of the left button
	{
		Left = NewInput;
	}
	else if (Key == "Right")//if it is the right button it will change the new input of the right button
	{
		Right = NewInput;
	}
	else if (Key == "Shoot")//if it is the shoot button it will change the new input of the shoot button
	{
		Shoot = NewInput;
	}
	return NewInput;
}