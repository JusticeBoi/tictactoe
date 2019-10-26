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
    private:
        Game* game_;

	    static constexpr uint_fast16_t alpha_max = 255*6;
	    static constexpr uint_fast16_t alpha_div = 6;

		uint_fast16_t alpha_tmp = 0;
};
#endif
