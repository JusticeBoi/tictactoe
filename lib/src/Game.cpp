#include "../inc/Game.hpp"
#include <random>



void Game::startTwoPlayer()
{
    FUNCTION_START;
    sf::RenderWindow w_(sf::VideoMode(800.f, 800.f), "Tic Tac Toe"); 
    turn_ = Turn::Human;

    while (w_.isOpen())
    {
        sf::Event event;
        while (w_.pollEvent(event))
        {
           switch(event.type)
           {
               case sf::Event::Closed:
                   w_.close();
                   break;
               case sf::Event::MouseButtonPressed:
                   if (event.mouseButton.button == sf::Mouse::Left)
                   {
                       sf::Vector2f mapped = w_.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                       Zone clickedZone = bc_.clickedZone(mapped);
                       if ( clickedZone != Zone::OUT )
                       {
                           if ( turn_ == Turn::Human )
                           {
                             if (bc_.fillZoneWith(clickedZone, XO::X )) turn_ = Turn::Machine;
                           }
                           else
                           {

                             if (bc_.fillZoneWith(clickedZone, XO::O )) turn_ = Turn::Human;
                           }
                           State s = isFinito();
                           if ( s != Game::State::NotFinished)
                           {
                               std::string win_msg = ( s == State::XWon ) ? "X won " : "O won";
                               std::cout << win_msg <<'\n';
                               w_.close();
                               
                           }

                       }

                   }
                   break;
           }

        }
        w_.clear();
        w_.draw(bc_);
        w_.display();
    }
    FUNCTION_END;
}

void Game::start(Turn startingTurn)
{
    FUNCTION_START;
    sf::RenderWindow w_(sf::VideoMode(800.f, 800.f), "Tic Tac Toe"); 
    turn_ = startingTurn;


    while (w_.isOpen())
    {
        sf::Event event;
        while (w_.pollEvent(event))
        {
            if ( turn_ == Turn::Human )
            {
                switch(event.type)
                {
                    case sf::Event::Closed:
                        w_.close();
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            sf::Vector2f mapped = w_.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                            Zone clickedZone = bc_.clickedZone(mapped);
                            if ( clickedZone != Zone::OUT )
                            {
                                if (bc_.fillZoneWith(clickedZone, XO::X )) turn_ = Turn::Machine;

                            }
                        }
                        break;
                }
            }
            else
            {
                this->makeBestMove(); turn_ = Turn::Human;
            }

        }
        State s = isFinito();
        if ( s != Game::State::NotFinished)
        {
            if ( s == Game::State::Draw ){ std::cout <<"Draw!"<<'\n'; w_.close(); break; };
            std::string win_msg = ( s == State::XWon ) ? "X won " : "O won";
            std::cout << win_msg <<'\n';
            w_.close();
        }

        w_.clear();
        w_.draw(bc_);
        w_.display();
    }
    FUNCTION_END;
}

int_fast8_t Game::minimax(std::array<XO,9>& board, XO player, int_fast8_t depth)
{
    auto won = BoardCell::hasWon(board);
    if (won.first != XO::None )
    {
        return (10-depth)*(won.first*player);
        //return won*player;
    }

    int_fast8_t score = -11;
    int_fast8_t move = -1;
    for(int i = 0 ; i < 9 ; ++i )
    {
        if( board[i] == XO::None )
        {
            board[i] = player;
            XO opponent = static_cast<XO>(-player);
            int_fast8_t lastScore = -minimax(board, opponent, depth+1); 
            if ( lastScore > score )
            {
                score = lastScore;
                move = i; 
            }
            board[i] = XO::None;
        }
    }
    if ( move == -1 ) return 0;
    return score;
}

int_fast8_t Game::makeBestMove() 
{
    std::array<XO,9>& board = bc_.getBoardRep();
    if ( std::all_of(board.begin(), board.end(), [](XO xo){return xo==XO::None;} ) )
    {
        std::random_device rd;
        std::uniform_int_distribution<int> dist(1, 9);
        return bc_.fillZoneWith(static_cast<Zone>(dist(rd)), XO::O);
    }
    int score = -10;
    Zone z = Zone::OUT;
    for(int i=0; i<9; i++)
    {
      if(board[i] == XO::None)
      {
        board[i] = XO::O;
        int tmpScore = -minimax(board, XO::X, 0);
        std::cout <<" i : " << i << " tmpScore : " << tmpScore <<'\n'; 
        board[i] = XO::None;
        if(tmpScore > score) 
        {
          score = tmpScore;
          z = static_cast<Zone>(i+1);
        }
      }
    }
    std::cout << "zone : " << z <<'\n';
    return bc_.fillZoneWith(z, XO::O);

}
void Game::run()
{
    FUNCTION_START;
    sf::RenderWindow App(sf::VideoMode(800.f, 800.f), "Tic Tac Toe"); 

    int screen = 0;
	std::vector<cScreen*> Screens;
	MenuScreen s0;
	Screens.push_back(&s0);
    TwoPlayerScreen twoPlayer(*this);
    Screens.push_back(&twoPlayer);
    VsAiScreen vsAi(*this);
    Screens.push_back(&vsAi);

	while (screen >= 0)
	{
		screen = Screens[screen]->Run(App);
	}

    FUNCTION_END;


}
BoardCell& Game::getBoardCell()
{
    return bc_;
}
Game::Turn& Game::getTurn()
{
    return turn_;
}
//void Game::drawWinningLine(sf::RenderWindow& rw)
//{
//    static bool winningLineFirstTime = false;
//    static sf::Clock c;
//    //if ( bc_.winningLine_.getSize() != sf::Vector2f{0,0} )
//    //{
//        if (!winningLineFirstTime)
//        {
//            int alpha = 0; 
//            int alpha_max = 5*255;  
//            int alpha_div = 5;
//            while(c.getElapsedTime().asSeconds() < 1.8f )
//            {
//                while ( alpha < alpha_max)
//	        	{
//                    ++alpha;
//                    rw.clear();
//                    bc_.winningLine_.setFillColor(sf::Color(255, 255, 255, alpha/alpha_div));
//                    rw.draw(bc_.winningLine_);
//                    rw.draw(bc_);
//                    rw.display();
//                }
//            }
//            winningLineFirstTime = true;
//        }
//    //}
//}

Game::State Game::isFinito() 
{
    //XO won = bc_.hasWOn();
    const std::array<XO,9>& board = bc_.getBoardRep();
    auto won = BoardCell::hasWon(board);
    if ( won.first != XO::None )
    {
        bc_.drawWinningLine(won.second);
        return ( won.first == XO::X ) ? Game::State::XWon : Game::State::OWon;  
    }
    else
    {
        return (std::any_of(board.begin(), board.end(),[](XO xo){return xo == XO::None;})) ? Game::State::NotFinished : Game::State::Draw;
    }
}
