#ifndef GAME__HPP_DEFINED
#define GAME__HPP_DEFINED

#include "../inc/screens.hpp"
#include "BoardCell.hpp"
#include <iostream>

class Game
{
    public:
        enum class State: uint_fast8_t
        {
            XWon = 0,
            OWon = 1,
            NotFinished = 2,
            Draw = 3
        };
        enum class Turn : bool
        {
            Human = true,
            Machine = false
        };
        Game() = default;
        ~Game() = default;
        State isFinito() ;
        int_fast8_t makeBestMove() ;
        std::pair<Zone,int> findBestMoveZone(XO player, bool ) ;
        void run();
        BoardCell& getBoardCell();
        Turn& getTurn();
        void drawWinningLine(sf::RenderWindow& rw);
        static bool finished;
        void fadeAway(sf::RenderWindow&, float);
        std::vector<int> getAllPossibleMovesIndices();
        void showAboutToLose();



    private:
        int_fast8_t minimax(std::array<XO,9>& board, XO player, int_fast8_t d);
        BoardCell bc_;
        Turn turn_;
        sf::RenderWindow* appPtr;
};

#endif // GAME__HPP_DEFINED 
