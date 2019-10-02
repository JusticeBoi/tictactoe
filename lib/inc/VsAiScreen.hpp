#ifndef VS_AI_SCREEN_HPP_INCLUDED
#define VS_AI_SCREEN_HPP_INCLUDED
#include <iostream>
#include "cScreen.hpp"
#include <SFML/Graphics.hpp>


class Game;
class VsAiScreen : public cScreen
{
    public:
    	VsAiScreen(Game& game); 
    	virtual int Run(sf::RenderWindow &App) override;
        void init() override;
    private:
        Game* game_;
	    int alpha_max;
	    int alpha_div;
        int allpha_tmp;

};
#endif
