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
    NowPlaying playing;
    NowPlaying wasPlaying;
    enum class Hover : uint8_t
    {
        EXIT = 0,
        CONTINUE = 1,
        PTOP = 2,
        PTOAI = 3,
        OUT = 4
    };
public:
	MenuScreen();
	virtual int Run(sf::RenderWindow &App);
};
#endif
