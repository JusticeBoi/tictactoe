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

	static constexpr uint_fast16_t alpha_max = 255*6;
	static constexpr uint_fast16_t alpha_div = 6;
	void init() override;

    Game* game_;
public:
	MenuScreen(Game& g);
    NowPlaying playing;
    NowPlaying wasPlaying;
	virtual int Run(sf::RenderWindow &App) override;
};
#endif
