#include "../inc/TwoPlayerScreen.hpp"
#include "Game.hpp"

TwoPlayerScreen::TwoPlayerScreen( Game& g  ): game_(&g){};
int TwoPlayerScreen::Run(sf::RenderWindow& App)
{
    using Turn = Game::Turn;
    using State = Game::State;
    sf::Event event;
    bool Running = true;
    BoardCell& boardCell = game_->getBoardCell();
    Game::Turn& turn = game_->getTurn();
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
                            State s = game_->isFinito();
                            if ( s != Game::State::NotFinished)
                            {
                                std::string win_msg = ( s == State::XWon ) ? "X won " : "O won";
                                std::cout << win_msg <<'\n';
                                Running = false;
                                //return 1;
                                //App.close();
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
        App.clear();
        App.draw(boardCell);
        App.display();
    }
    sf::Clock c;
    while(c.getElapsedTime().asSeconds() < 2.0f )
    {
        App.display();
    }
	return -1;
}
