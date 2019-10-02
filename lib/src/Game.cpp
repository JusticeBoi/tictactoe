#include "../inc/Game.hpp"
#include <random>


bool Game::finished = false;

int_fast8_t Game::minimax(std::array<XO,9>& board, XO player, int_fast8_t depth)
{
    auto won = BoardCell::hasWon(board);
    if (won.first != XO::None )
    {
        int_fast8_t ret = (10-depth)*(won.first*player); 
        //std::cout << "from minimax : " << static_cast<int>(ret) <<'\n';
        return ret;
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

std::pair<Zone, int> Game::findBestMoveZone(XO player, bool checkStartPosition ) 
{
    #ifdef WITH_FUNCTION_UTILITIES
    SCOPED_FUNCTION_START;
    #endif
    std::array<XO,9>& board = bc_.getBoardRep();
    if ( checkStartPosition)
    {
        if ( std::all_of(board.begin(), board.end(), [](XO xo){return xo==XO::None;} ) )
        {
            //std::random_device rd;
            std::mt19937 mt(time(NULL));
            std::uniform_int_distribution<int> dist(1, 9);
            return std::make_pair(static_cast<Zone>(dist(mt)),-1);
        }
    }
    int score = -10;
    Zone z = Zone::OUT;
    for(int i=0; i<9; i++)
    {
      if(board[i] == XO::None)
      {
        board[i] = player;
        int tmpScore = -minimax(board, static_cast<XO>(-player), 0);
        //std::cout <<" i : " << i << " tmpScore : " << tmpScore <<'\n'; 
        board[i] = XO::None;

        if(tmpScore > score) 
        {
          score = tmpScore;
          z = static_cast<Zone>(i+1);
          //std::cout <<"new score : " << tmpScore <<"of zone : "<< i+1 <<'\n';
        }
      }
    }
    return std::make_pair(z,score);
    #ifdef WITH_FUNCTION_UTILITIES
    SCOPED_FUNCTION_END;
    #endif
}
int_fast8_t Game::makeBestMove() 
{
    std::array<XO,9>& board = bc_.getBoardRep();
    if ( std::all_of(board.begin(), board.end(), [](XO xo){return xo==XO::None;} ) )
    {
        //std::random_device rd;
        std::mt19937 mt(time(NULL));
        std::uniform_int_distribution<int> dist(1, 9);
        return bc_.fillZoneWith(static_cast<Zone>(dist(mt)), XO::O);
    }
    auto bestMovePair = findBestMoveZone(XO::O,false);
    if ( bestMovePair.second == 10 ) 
    {
        showAboutToLose();
    }
    return bc_.fillZoneWith(bestMovePair.first, XO::O);

}
void Game::showAboutToLose()
{
    sf::Texture texture;
    sf::Sprite sp;
	if (!texture.loadFromFile("../themes/crying.png" ))
	{
		return ;
	}
    sp.setTexture(texture);
    sf::Clock c;
    int alpha = 0;
	sp.setColor(sf::Color(255, 255, 255, alpha));
    static const int alpha_div = 5;
    static const int alpha_max = 255*5;
    //int alpha_tmp = 0;
    while(c.getElapsedTime().asSeconds() < 1.2f )
    {
          alpha = (alpha + 1 != alpha_max ) ? alpha + 1 : alpha_max;
          //alpha_tmp = alpha / alpha_div;
          appPtr->clear();
	      sp.setColor(sf::Color(255, 255, 255, alpha/alpha_div));
          appPtr->draw(sp);
          appPtr->draw(bc_);
          appPtr->display();
    }

}
void Game::run()
{
    #ifdef WITH_FUNCTION_UTILITIES
    FUNCTION_START;
    #endif
    sf::RenderWindow App(sf::VideoMode(800.f, 800.f), "Tic Tac Toe"); 
    appPtr = &App;

    int screen = 0;
    int old_screen = 0;
	std::vector<cScreen*> Screens;

	MenuScreen s0;
	Screens.push_back(&s0);
    TwoPlayerScreen twoPlayer(*this);
    Screens.push_back(&twoPlayer);
    VsAiScreen vsAi(*this);
    Screens.push_back(&vsAi);

	while (screen >= 0)
	{
        old_screen = screen;
		screen = Screens[screen]->Run(App);
        if ( finished ) 
        {
            //std::cout <<"finished" <<'\n';
            bc_.cleanUpForNextRound();
            turn_ = Turn::Machine;
            std::for_each(Screens.begin(), Screens.end(), [](cScreen* scr ){scr->init();});
            finished = false;
        }
	}

    #ifdef WITH_FUNCTION_UTILITIES
    FUNCTION_END;
    #endif


}
BoardCell& Game::getBoardCell()
{
    return bc_;
}
Game::Turn& Game::getTurn()
{
    return turn_;
}

void Game::fadeAway(sf::RenderWindow& rw, float secs)
{
  sf::Clock c;
  int alpha = 255*6;
  static const int alpha_div = 6;
  static const int alpha_max = 255*6;
  int alpha_tmp = 0;
    while(c.getElapsedTime().asSeconds() < secs )
    {
          alpha = (alpha - 1 != 0 ) ? alpha -1 : 0;
          alpha_tmp = alpha / alpha_div;
          appPtr->clear();
    	    bc_.setOutlineColor(sf::Color(255, 255, 255, alpha_tmp));
          appPtr->draw(bc_);
          appPtr->display();
    }
}
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
