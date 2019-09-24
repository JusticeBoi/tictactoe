#include <iostream>
//#include "../lib/inc/Board.hpp"
//#include "../lib/inc/BoardCell.hpp"
#include "../lib/inc/Game.hpp"

#ifdef TICTACTOE_WIN_32
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
#else
int main()
#endif
{
    #ifdef WITH_FUNCTION_UTILITIES
        utilities::LogConfiguration::fancy = true;
        utilities::LogConfiguration::catchSignals = false;
        utilities::LogConfiguration::showLoopSummary = true;
        utilities::LogConfiguration::showProgressbar = true;
        utilities::LogConfiguration::showTimingSummary = false;
        std::string TicTacToeHeader = utilities::LogConfiguration::getTicTactoe( );
        utilities::log(TicTacToeHeader, utilities::LogLevels::ERROR );
    #endif

    Game game;
    game.run();

    return 0;
}
