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
    virtual int Run (sf::RenderWindow &App) = 0;
    virtual int loadFromFile (const std::string& str) ; 
protected:
    
    sf::Texture texture;
	sf::Sprite sprite;
    
};

#endif
