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
        void start(Turn startingTurn);
        void startTwoPlayer();
        State isFinito() ;
        int_fast8_t makeBestMove() ;
        void run();
        BoardCell& getBoardCell();
        Turn& getTurn();
        void drawWinningLine(sf::RenderWindow& rw);

    private:
        int_fast8_t minimax(std::array<XO,9>& board, XO player, int_fast8_t d);
        BoardCell bc_;
        Turn turn_;
};

#endif // GAME__HPP_DEFINED 
