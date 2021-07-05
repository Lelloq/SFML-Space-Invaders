#include <SFML/Graphics.hpp>
#include "Block.h"

sf::Sprite Block::DrawBlock(int iState)//Returns the sprite depending on the parameter value
{
	switch (iState)
	{
	case 0:
		return FBlock;//Sprite for FullBlock.png
		break;
	case 1:
		return OKBlock;//Sprite for OkBlock.png
		break;
	case 2:
		return WBlock;//Sprite for WeakBlock.png
		break;
	}
	return FBlock;//There for to avoid warnings
}