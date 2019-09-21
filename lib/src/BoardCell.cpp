#include "../inc/BoardCell.hpp"
#include <algorithm>
#include <iostream>
#include <memory>





BoardCell::BoardCell()
{
    //auto font = std::make_shared<sf::Font>();
    if (!font_.loadFromFile("../fonts/GlacialIndifference.otf"))
    {
        throw std::runtime_error("couldnt load font");
        // error...
    }

    auto gen = [this]()
    {
        static int i = 1;
        static int j = 1;
        Cell c; 
        std::cout <<"i : "<< i << " j : " << j<<'\n';
        c.setFont(font_);
        c.setPosition(offset + ((i-1)*Cell::width), offset + ((j-1)*Cell::height));
        c.setZone( static_cast<Zone>(3*(j-1) + i));
        j = ( (i % 3) ) ? j : j+1; 
        i = ( i == 3) ? 1 : i+1;
        return c;
    };
    std::generate(board_.begin(), board_.end(), gen);
    std::fill(boardRep.begin(), boardRep.end(), XO::None);

}

void BoardCell::draw(sf::RenderTarget& target, sf::RenderStates /*states*/) const
{
    std::for_each(board_.begin(), board_.end(), [&target](const Cell& c){ target.draw(c);});

}

bool BoardCell::fillZoneWith( Zone zone, XO xOrO )
{
    if ( board_[zone - 1].getXO() == XO::None ) 
    {
        board_[zone-1].setXO(xOrO);
        boardRep[zone-1] = xOrO;
        return 1;
    }
    else
    {
        return 0;
    }
}
Zone BoardCell::clickedZone(const sf::Vector2f& v) const
{
    SCOPED_FUNCTION_START;
    auto f = std::find_if(board_.cbegin(), board_.cend(), [&v]( const Cell& c){ return c.contains(v);}); 

    return ( f != board_.cend() ) ? f->getZone() : Zone::OUT;
    SCOPED_FUNCTION_END;
}
//XO BoardCell::hasWOn() const
//{
//    SCOPED_FUNCTION_START;
//    auto rowComparator = [](const auto begit ) -> XO
//    {
//        auto begin = begit;
//        if ( begin->getXO() == XO::X )
//        {
//            return ( ((++begin)->getXO() == XO::X && (++begin)->getXO() == XO::X) ? XO::X : XO::None   );
//        }
//        else if ( begit->getXO() == XO::O)
//        {
//            return ( ((++begin)->getXO() == XO::O && (++begin)->getXO() == XO::O) ? XO::O : XO::None  );
//        }
//        else
//        {
//            return XO::None;
//        }
//    };
//    auto colComparator = [](auto begin ) -> XO
//    {
//        if ( begin->getXO() == XO::X )
//        {
//            return ( ((begin+3)->getXO() == XO::X && (begin+6)->getXO() == XO::X) ? XO::X : XO::None   );
//        }
//        else if ( begin->getXO() == XO::O)
//        {
//            return ( ((begin+3)->getXO() == XO::O && (begin+6)->getXO() == XO::O) ? XO::O : XO::None  );
//        }
//        else
//        {
//            return XO::None;
//        }
//    };
//    XO firstRowResult = rowComparator(board_.cbegin());
//    XO secondRowResult = rowComparator(board_.cbegin()+3);
//    XO thirdRowResult = rowComparator(board_.cbegin()+6);
//
//    if ( firstRowResult != XO::None ) return firstRowResult;  
//    if ( secondRowResult != XO::None ) return secondRowResult;  
//    if ( thirdRowResult != XO::None ) return thirdRowResult;  
//
//    XO firstColResult = colComparator(board_.cbegin());
//    XO secondColResult = colComparator(board_.cbegin()+1);
//    XO thirdColResult = colComparator(board_.cbegin()+2);
//
//    if ( firstColResult != XO::None ) return firstColResult;  
//    if ( secondColResult != XO::None ) return secondColResult;  
//    if ( thirdColResult != XO::None ) return thirdColResult;  
//
//
//    if ( board_[0].getXO() != XO::None && board_[4].getXO() == board_[0].getXO() &&  board_[4].getXO() == board_[8].getXO() )
//    {
//        return board_[8].getXO();
//    }
//    if ( board_[2].getXO() != XO::None && board_[4].getXO() == board_[2].getXO() &&  board_[4].getXO() == board_[6].getXO() )
//    {
//        return board_[6].getXO();
//    }
//    return XO::None; 
//    SCOPED_FUNCTION_END;
//
//}

std::array<XO,9>& BoardCell::getBoardRep()
{
    return boardRep;
}
const std::array<XO,9>& BoardCell::getBoardRep() const
{
    return boardRep;
}
XO BoardCell::hasWonNew() const
{
    SCOPED_FUNCTION_START;
    static unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(boardRep[wins[i][0]] != XO::None &&
           boardRep[wins[i][0]] == boardRep[wins[i][1]] &&
           boardRep[wins[i][0]] == boardRep[wins[i][2]])
            return boardRep[wins[i][2]];
    }
    return XO::None;
    SCOPED_FUNCTION_END;
}
XO BoardCell::hasWon(const std::array<XO,9>& board) 
{
    static unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != XO::None &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return XO::None;
}
