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
    	virtual int Run(sf::RenderWindow &App);
    private:
        Game* game_;
	    int alpha_max;
	    int alpha_div;

};
#endif
