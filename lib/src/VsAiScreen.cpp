#include "../inc/VsAiScreen.hpp"
#include "Game.hpp"

void VsAiScreen::init()
{
	alpha_max = 6 * 255;
	alpha_div = 6;
}
VsAiScreen::VsAiScreen( Game& g  ): game_(&g){
    init();
};

int VsAiScreen::Run(sf::RenderWindow& App)
{
    using Turn = Game::Turn;
    using State = Game::State;
	int alpha = 0;
    int allpha_tmp = 0;
    sf::Event event;
    bool Running = true;
    BoardCell& boardCell = game_->getBoardCell();
    Game::Turn& turn = game_->getTurn();

    while ( Running )
    {
        while (App.pollEvent(event))
        {
            if ( turn == Turn::Human )
            {
                switch(event.type)
                {
                    case sf::Event::Closed:
                        return -1;
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            sf::Vector2f mapped = App.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                            Zone clickedZone = boardCell.clickedZone(mapped);
                            if ( clickedZone != Zone::OUT )
                            {
                                if (boardCell.fillZoneWith(clickedZone, XO::X )) turn = Turn::Machine;
                            }
                        }
                        break;
                case sf::Event::KeyPressed:
                    {
                        if ( event.key.code == sf::Keyboard::Escape ) 
                        {
					        return 0;
                        }
                        break;
                    }
                }
            }
            else
            {
                game_->makeBestMove(); turn = Turn::Human;
            }
        }
        State s = game_->isFinito();
        if ( s != Game::State::NotFinished)
        {
            if ( s == Game::State::Draw ){ std::cout <<"Draw!"<<'\n'; }
            else 
            {
                std::string win_msg = ( s == State::XWon ) ? "X won " : "O won";
                std::cout << win_msg <<'\n';
                sf::Clock c;
                while(c.getElapsedTime().asSeconds() < 1.5f )
                {
                    while ( alpha != 0)
	            	{
	            		--alpha;
                        allpha_tmp = alpha / alpha_div;
	            	    boardCell.setOutlineColor(sf::Color(255, 255, 255, allpha_tmp));
                        App.clear();
                        App.draw(boardCell);
                        App.display();
	            	}
                }
            }
            Game::finished = true;
            Running = false;
            return 0 ;
            //Running = false;
        }
		if (alpha<alpha_max)
		{
			++alpha;
		}
        allpha_tmp = alpha / alpha_div;
		boardCell.setOutlineColor(sf::Color(255, 255, 255, allpha_tmp));
        App.clear();
        App.draw(boardCell);
        App.display();
    }
    return -1;
}