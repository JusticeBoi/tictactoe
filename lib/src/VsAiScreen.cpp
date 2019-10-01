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
	sf::Font Font;
	sf::Text Tip;
	if (!Font.loadFromFile("../fonts/Inconsolata.ttf"))
	{
		std::cerr << "Error loading Inconsolata.ttf" << std::endl;
		return (-1);
	}

	Tip.setFont(Font);
	Tip.setCharacterSize(40);
	Tip.setString("Tip");
	Tip.setPosition({ 700.f, 50.f });
    Tip.setFillColor(sf::Color(255, 255, 255, 255));

    Hover hover  = Hover::OUT; 
    Zone play_tip = Zone::OUT;

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
                            else if ( Tip.getGlobalBounds().contains(mapped) )
                            {
                                XO player = (turn == Turn::Human ) ? XO::X : XO::O;
                                play_tip = game_->findBestMoveZone(player, true);
                                boardCell.fillZoneWith(play_tip, player);
                                sf::Clock c;
                                Cell& cellToDraw = boardCell.getBoard()[play_tip - 1];
                                cellToDraw.setSymbolColor(sf::Color(255, 0, 0, 20));
                                while(c.getElapsedTime().asSeconds() < 0.3f )
                                {
                                        App.draw(boardCell.getBoard()[play_tip - 1]);
                                        App.display();
                                }
                                boardCell.eraseZoneState(play_tip);
                                cellToDraw.setSymbolColor(sf::Color(255, 255, 255, 255));
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
                case sf::Event::MouseMoved:
                    {
                        sf::Vector2f mapped = App.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
                        if ( Tip.getGlobalBounds().contains(mapped) ) { hover = Hover::TIP;}  
                        else
                        {
                            hover = Hover::OUT;
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
            if ( s == Game::State::Draw )
            {
                game_->fadeAway(App, 0.7f);
            }
            else 
            {
                std::string win_msg = ( s == State::XWon ) ? "X won " : "O won";
                std::cout << win_msg <<'\n';
                sf::Clock c;
                game_->fadeAway(App, 0.7f);
            }
            Game::finished = true;
            Running = false;
            return 0 ;
        }
		if (alpha<alpha_max)
		{
			++alpha;
		}
        switch ( hover )
        {
            case Hover::TIP:
            {
                Tip.setFillColor(sf::Color(255, 0, 0, 255));
                break;
            }
            case Hover::OUT:
            {
                Tip.setFillColor(sf::Color(255, 255, 255, 255));
                break;
            }
            default:
                break;
        }
        allpha_tmp = alpha / alpha_div;
		boardCell.setOutlineColor(sf::Color(255, 255, 255, allpha_tmp));
        App.clear();
        App.draw(boardCell);
        App.draw(Tip);
        App.display();
    }
    return -1;
}
