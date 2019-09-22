#include "../inc/cScreen.hpp"
#include <iostream>


int cScreen::loadFromFile(const std::string& s)
{
	if (!texture.loadFromFile(s))
	{
		return 0;
	}
    sprite.setTexture(texture);
    return 1;
    
}
