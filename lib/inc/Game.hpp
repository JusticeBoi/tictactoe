#ifndef GAME__HPP_DEFINED
#define GAME__HPP_DEFINED

#include "BoardCell.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>


class Game
{
    enum class State: short
    {
        XWon = 0,
        OWon = 1,
        NotFinished = 2,
        Draw = 3
    };
    public:
        enum class Turn : bool
        {
            Human = true,
            Machine = false
        };
        Game() = default;
        ~Game() = default;
        void start(Turn startingTurn);
        void startTwoPlayer();
        State isFinito() const;
        int makeBestMove() ;
        int minimax(std::array<XO,9>& board, XO player, int d);
    private:
        BoardCell bc_;
        Turn turn_;

};

#endif // GAME__HPP_DEFINED 