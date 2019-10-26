#ifndef TWO_PLAYER_SCREEN_HPP_INCLUDED
#define TWO_PLAYER_SCREEN_HPP_INCLUDED
#include <iostream>
#include "cScreen.hpp"
#include <SFML/Graphics.hpp>


class Game;
class TwoPlayerScreen : public cScreen
{
    public:
    	TwoPlayerScreen(Game& game); 
    	virtual int Run(sf::RenderWindow &App) override;
    private:
        Game* game_;
	    static constexpr uint_fast16_t alpha_max = 255*6;
	    static constexpr uint_fast16_t alpha_div = 6;
		uint_fast16_t alpha_tmp = 0;

};
#endif
