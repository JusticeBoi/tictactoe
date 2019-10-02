#ifndef MENUSCREEN_HPP_INCLUDED
#define MENUSCREEN_HPP_INCLUDED

#include <iostream>
#include "cScreen.hpp"

#include <SFML/Graphics.hpp>

class Game;
class MenuScreen : public cScreen
{
private:
    using cScreen::NowPlaying;

	int alpha_max;
	int alpha_div;
    Game* game_;
public:
    void init() override;
	MenuScreen(Game& g);
    NowPlaying playing;
    NowPlaying wasPlaying;
	virtual int Run(sf::RenderWindow &App) override;
};
#endif
