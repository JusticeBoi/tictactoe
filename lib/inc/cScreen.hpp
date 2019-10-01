#ifndef CSCREEN_HPP_INCLUDED
#define CSCREEN_HPP_INCLUDED

#include <SFML/Graphics.hpp>
class cScreen
{
public :
    enum NowPlaying : uint_fast8_t
    {
        NOTHING = 0,
        PVSP = 1,
        PVSAI = 2
    };
    enum class Hover : uint8_t
    {
        EXIT = 0,
        CONTINUE = 1,
        PTOP = 2,
        PTOAI = 3,
        OUT = 4,
        TIP = 5
    };
    virtual int Run (sf::RenderWindow &App) = 0;
    virtual int loadFromFile (const std::string& str) ; 
    bool finished_;
    virtual void init() = 0;
protected:
    
    sf::Texture texture;
	sf::Sprite sprite;
    
};

#endif
