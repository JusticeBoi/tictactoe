#include "../inc/BoardCell.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <limits>
#include <cmath>



void BoardCell::cleanUp()
{
    std::fill(boardRep_.begin(), boardRep_.end(), XO::None);
	std::for_each(board_.begin(), board_.end(), [](Cell& c) { c.setXO(XO::None); });
    winningLine_ = sf::RectangleShape();
    winningLine_.setOutlineColor(sf::Color::White);
    numberOfEmpty = 9;
}

void BoardCell::init()
{
    if (!font_.loadFromFile("../fonts/GlacialIndifference.otf"))
    {
        throw std::runtime_error("couldnt load font");
        // error...
    }
    static int i = 1;
    static int j = 1;

    auto gen = [this]()
    {
        Cell c; 

        c.setFont(font_);
        c.setPosition(offset + ((i-1)*Cell::width), offset + ((j-1)*Cell::height));
        c.setZone( static_cast<Zone>(3*(j-1) + i));

        j = ( (i % 3) ) ? j : j+1; 
        i = ( i == 3) ? 1 : i+1;
        return c;
    };
    std::generate(board_.begin(), board_.end(), gen);
    std::fill(boardRep_.begin(), boardRep_.end(), XO::None);
    winningLine_ = sf::RectangleShape();
    winningLine_.setOutlineColor(sf::Color::White);

    i = 1;
    j = 1;
}
BoardCell::BoardCell()
{
    init();
}

void BoardCell::draw(sf::RenderTarget& target, sf::RenderStates /*states*/) const
{
    std::for_each(board_.begin(), board_.end(), [&target](const Cell& c){ target.draw(c);});
    if ( winningLine_.getSize() != sf::Vector2f{0,0} )
    {
            target.draw(winningLine_);
    }
}

void BoardCell::setOutlineColor(const sf::Color& c)
{
    std::for_each(board_.begin(), board_.end(),[&c](Cell& cell){cell.setOutlineColor(c);});
    winningLine_.setFillColor(sf::Color(192,192,192,c.a));
}
bool BoardCell::fillZoneWith( Zone zone, XO xOrO )
{
    if ( board_[zone - 1].getXO() == XO::None ) 
    {
        board_[zone-1].setXO(xOrO);
        boardRep_[zone-1] = xOrO;
        --numberOfEmpty;
        return 1;
    }
    else
    {
        return 0;
    }
}
bool BoardCell::eraseZoneState( Zone zone )
{
    if ( board_[zone - 1].getXO() == XO::None ) 
    {
        return 0;
    }
    else
    {
        board_[zone-1].setXO(XO::None);
        boardRep_[zone-1] = XO::None;
        ++numberOfEmpty;
        return 1;
    }
}
Zone BoardCell::clickedZone(const sf::Vector2f& v) const
{
    #ifdef WITH_FUNCTION_UTILITIES
    SCOPED_FUNCTION_START;
    #endif
    auto f = std::find_if(board_.cbegin(), board_.cend(), [&v]( const Cell& c){ return c.contains(v);}); 

    return ( f != board_.cend() ) ? f->getZone() : Zone::OUT;
    #ifdef WITH_FUNCTION_UTILITIES
    SCOPED_FUNCTION_END;
    #endif
}
const std::array<Cell,9>& BoardCell::getBoard() const
{
    return board_;
}
std::array<Cell,9>& BoardCell::getBoard() 
{
    return board_;
}
std::array<XO,9>& BoardCell::getBoardRep()
{
    return boardRep_;
}
const std::array<XO,9>& BoardCell::getBoardRep() const
{
    return boardRep_;
}
void BoardCell::drawWinningLine( const threeInt& tup )
{
    const int from = std::get<0>(tup);
    const int to = std::get<2>(tup);

    const Cell fromCell = board_[from];
    const Cell toCell = board_[to];

    const sf::Vector2f fromPos = fromCell.getPosition();
    const sf::Vector2f toPos = toCell.getPosition();

    const sf::Vector2f midPointFrom = fromPos + sf::Vector2f{fromCell.width/2, fromCell.height/2};
    const sf::Vector2f midPointTo = toPos + sf::Vector2f{toCell.width/2, toCell.height/2};

    const float size = std::sqrt(std::pow(midPointFrom.y - midPointTo.y,2) + std::pow(midPointFrom.x - midPointTo.x,2));
    winningLine_ = sf::RectangleShape(sf::Vector2f(size, 5.f));
    if ( (from == 0 && to == 6) || (from == 1 && to == 7) || (from == 2 && to == 8) )
    {
        winningLine_.rotate(90.f);
    }
    else if ( from == 2 && to == 6 ) winningLine_.rotate(135.f);
    else if ( from == 0 && to == 8 ) winningLine_.rotate(45.f);
    winningLine_.setPosition(midPointFrom);

}
std::pair<XO, BoardCell::threeInt> BoardCell::hasWon(const std::array<XO,9>& board) 
{
    static const int wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    for(int i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != XO::None &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return std::make_pair(board[wins[i][2]], threeInt{wins[i][0], wins[i][1], wins[i][2]});
    }
    static const int max = std::numeric_limits<int>::max();
    return std::make_pair(XO::None, threeInt{max, max, max});
}

void BoardCell::cleanUpForNextRound()
{
	cleanUp();
}
