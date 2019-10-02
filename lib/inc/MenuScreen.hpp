#ifndef MENUSCREEN_HPP_INCLUDED
#define MENUSCREEN_HPP_INCLUDED

#include <iostream>
#include "cScreen.hpp"

#include <SFML/Graphics.hpp>

class MenuScreen : public cScreen
{
private:
    using cScreen::NowPlaying;

	int alpha_max;
	int alpha_div;
public:
    void init() override;
	MenuScreen();
    NowPlaying playing;
    NowPlaying wasPlaying;
	virtual int Run(sf::RenderWindow &App) override;
};
#endif
