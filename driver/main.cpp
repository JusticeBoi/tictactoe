#include <iostream>
#include "../lib/inc/Game.hpp"

int main()
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
