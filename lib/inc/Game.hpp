#ifndef GAME__HPP_DEFINED
#define GAME__HPP_DEFINED

#include "BoardCell.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>


class Game
{
    enum class Turn : bool
    {
        Human = true,
        Machine = false
    };
    enum class State: short
    {
        XWon = 0,
        OWon = 1,
        NotFinished = 2
    };
    public:
        Game() = default;
        ~Game() = default;
        void start();
        State isFinito() const;
    private:
        BoardCell bc_;
        Turn turn_;

};

#endif // GAME__HPP_DEFINED 
