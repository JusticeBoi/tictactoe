#ifndef CSCREEN_HPP_INCLUDED
#define CSCREEN_HPP_INCLUDED
#include <TGUI/TGUI.hpp>
class cScreen
{
public :
    virtual int Run (sf::RenderWindow &App) = 0;
};

#endif
