#include "../inc/TwoPlayerScreen.hpp"
#include "Game.hpp"

void TwoPlayerScreen::init()
{
	alpha_max = 6 * 255;
	alpha_div = 6;
}
TwoPlayerScreen::TwoPlayerScreen( Game& g  ): game_(&g)
{
    init();
};
int TwoPlayerScreen::Run(sf::RenderWindow& App)
{
    using Turn = Game::Turn;
    using State = Game::State;

    sf::Event event;
	int alpha = 0;
    int allpha_tmp = 0;

    bool Running = true;
    BoardCell& boardCell = game_->getBoardCell();
	boardCell.setOutlineColor(sf::Color(255, 255, 255, alpha));
    Game::Turn& turn = game_->getTurn();
    Game::State s = Game::State::NotFinished;
    while ( Running )
    {
        while (App.pollEvent(event))
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
                            if ( turn == Game::Turn::Human )
                            {
                              if (boardCell.fillZoneWith(clickedZone, XO::X )) turn = Turn::Machine;
                            }
                            else
                            {

                              if (boardCell.fillZoneWith(clickedZone, XO::O )) turn = Turn::Human;
                            }
                            s = game_->isFinito();
                            if ( s != Game::State::NotFinished)
                            {
                                if ( s == Game::State::Draw ){ std::cout <<"Draw!"<<'\n'; }
                                else
                                {
                                    std::string win_msg = ( s == State::XWon ) ? "X won " : "O won";
                                    std::cout << win_msg <<'\n';
                                    Game::finished = true;
                                    Running = false;
                                    sf::Clock c;
                                    while(c.getElapsedTime().asSeconds() < 1.5f )
                                    {
                                        while ( alpha != 0)
	                                	{
	                                		--alpha;
                                            allpha_tmp = alpha / alpha_div;
                                            App.clear();
	                                	    boardCell.setOutlineColor(sf::Color(255, 255, 255, allpha_tmp));
                                            App.draw(boardCell);
                                            App.display();
	                                	}
                                    }
                                }
                                return 0;
                            }
                        }

                    }
                    break;
                case sf::Event::KeyPressed:
                    {
                        if ( event.key.code == sf::Keyboard::Escape ) 
                        {
                            std::cout <<"escapd pressed"<<'\n';
					        return 0;
                        }
                        break;
                    }
            }
        }
		if (alpha<alpha_max)
		{
			++alpha;
		}
        allpha_tmp = alpha / alpha_div;
		boardCell.setOutlineColor(sf::Color(255, 255, 255, allpha_tmp));
        App.clear();
        App.draw(boardCell);
        //if ( s == Game::State::XWon || s == Game::State::OWon )
        //{
        //    game_->drawWinningLine(App);
        //}
        App.display();
    }
	return -1;
}
