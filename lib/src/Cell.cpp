#include "../inc/Cell.hpp"
#include <iostream>
#include <string>
#include "utilities/inc/logging.hpp"
#include "utilities/inc/functionessentials.hpp"


Cell::Cell()
{
    xo_ = XO::None;

  rec_.setFillColor(sf::Color::Transparent);
  rec_.setOutlineColor(sf::Color::White);
  rec_.setOutlineThickness(borderThickness);
  rec_.setSize(sf::Vector2f(width, height));

  symbol_.setString(" ");
  symbol_.setCharacterSize(1600.f/9.f);
  symbol_.setFillColor(sf::Color::Cyan);
}



bool Cell::contains(const sf::Vector2f& v) const {
  sf::FloatRect rect = rec_.getGlobalBounds();
  if(v.x >= rect.left &&
     v.x <= rect.left + rect.width &&
     v.y >= rect.top &&
     v.y <= rect.top + rect.height)
    return true;
  return false;
}

void Cell::setXO(XO x_or_o )
{
    xo_ = x_or_o;
  if(xo_ == XO::X)
  {
    symbol_.setString("X");
    this->setPosition(rec_.getPosition());
  }
  else if(xo_ == XO::O)
  {
    symbol_.setString("O");
    this->setPosition(rec_.getPosition());
  }
  else
    symbol_.setString(" ");
}

void Cell::setPosition(float x, float y )
{
    rec_.setPosition(x,y);
    if ( xo_ == XO::X )
    {
        symbol_.setPosition(x+textXOffsetX,y+textYOffsetX);
    }
    else
    {    
        symbol_.setPosition(x+textXOffsetO,y+textYOffsetO);
    
    }

}
void Cell::setPosition(const sf::Vector2f& p )
{
    setPosition(p.x,p.y);
}

const sf::Vector2f& Cell::getPosition( ) const
{
    return rec_.getPosition();
}
XO Cell::getXO( )
{
    return xo_;
}
void Cell::setFont(const sf::Font& sf)
{
    font_ = sf;
    symbol_.setFont(sf);
}

void Cell::setZone(Zone z)
{
    z_ = z;
}

Zone Cell::getZone() const
{
    return z_;
}
XO Cell::getXO() const
{
    return xo_;
}
void Cell::draw(sf::RenderTarget& target, sf::RenderStates /*states*/) const {
  target.draw(rec_);
  if(xo_ != XO::None)
    target.draw(symbol_);
}
