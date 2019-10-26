#ifndef SCREEN_1_HPP_INCLUDED
#define SCREEN_1_HPP_INCLUDED
#include <iostream>
#include "cScreen.hpp"

#include <SFML/Graphics.hpp>

class screen_1 : public cScreen
{
private:
	float movement_step;
	float posx;
	float posy;
	sf::RectangleShape Rectangle;
public:
	screen_1();
	virtual int Run(sf::RenderWindow &App) override;
};

#endif
