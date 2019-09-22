#ifndef BOARD__CELL__HPP_DEFINED
#define BOARD__CELL__HPP_DEFINED

#include <array>
#include "Cell.hpp"

class BoardCell : public sf::Drawable
{

    public:
        BoardCell();
        BoardCell(const BoardCell&) = delete;
        BoardCell(BoardCell&&) = delete;

        static constexpr float width = 2.f*800.f/3.f;
        static constexpr float height = 2.f*800.f/3.f;
        static constexpr float offset = 800.f/6.f;



        void draw(sf::RenderTarget& target, sf::RenderStates /*states*/) const override  ;
        Zone clickedZone(const sf::Vector2f& v) const;
        /* return 1 if fill succesful, meaning that the place was empty and now filled
         * if place was already full, no filling is done and false is returned*/
        bool fillZoneWith( Zone zone, XO xOrO );
        //XO hasWOn() const ;
        XO hasWonNew() const ;
        static XO hasWon(const std::array<XO,9>& board) ;

        std::array<XO,9>& getBoardRep();
        const std::array<XO,9>& getBoardRep() const;

    private:
        std::array<Cell,9> board_;
        std::array<XO,9> boardRep;
        
        sf::Font font_;

};



#endif // BOARD__CELL__HPP_DEFINED
