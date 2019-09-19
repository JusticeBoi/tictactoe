#include "../inc/Board.hpp"
#include <iostream>


Board::Board( const sf::Vector2f & windowSize ) : m_lines(sf::Lines,8), m_ticks(sf::Lines,36)
{
    m_circles.reserve(5);
    for(int i = 0; i < 9 ; ++i) occupied[i] = false;

    float w = 2.f*windowSize.x/3.f;
    float h = 2.f*windowSize.y/3.f;
    m_dims = {w,h};
    m_tic_dist = {w/3.f,h/3.f};




    float offset_x = windowSize.x/6.f;
    float offset_y = windowSize.y/6.f;
    m_offset = {offset_x, offset_y};

    m_rect = sf::RectangleShape(sf::Vector2f(w,h)); 
    m_rect.setPosition(offset_x, offset_y);


    m_lines[0].position = sf::Vector2f(offset_x, offset_y + h/3.f);
    m_lines[1].position = sf::Vector2f(offset_x + w, offset_y + h/3.f);

    m_lines[2].position = sf::Vector2f(offset_x, offset_y + (2.f*h/3.f));
    m_lines[3].position = sf::Vector2f(offset_x + w, offset_y + (2.f*h/3.f));

    m_lines[4].position = sf::Vector2f(offset_x + w/3.f, offset_y);
    m_lines[5].position = sf::Vector2f(offset_x + w/3.f , offset_y + h);

    m_lines[6].position = sf::Vector2f(offset_x + (2.f*w/3.f), offset_y);
    m_lines[7].position = sf::Vector2f(offset_x + (2.f*w/3.f) , offset_y + h);

    
    for (int i = 0; i < 8 ; ++i ) m_lines[i].color = sf::Color::Black;
}
bool Board::contains(const sf::Vector2f& v2)
{
    auto gb = m_rect.getGlobalBounds();
    return gb.contains(v2.x, v2.y);

}
void Board::drawMoveIn(Zones zone, XO x_or_o)
{
    if ( zone == Zones::ONE && !occupied[zone-1] )
    {
        if ( x_or_o == XO::X)
        {
            m_ticks[0].position = sf::Vector2f(m_offset.x, m_offset.y);
            m_ticks[1].position = sf::Vector2f(m_offset.x+m_tic_dist.x, m_offset.y + m_tic_dist.y);

            m_ticks[2].position = sf::Vector2f(m_offset.x+m_tic_dist.x, m_offset.y);
            m_ticks[3].position = sf::Vector2f(m_offset.x, m_offset.y + m_tic_dist.y);
            for(int i = 0; i < 4 ; ++i ) m_ticks[i].color = sf::Color::Blue;
        }
        else
        {
            sf::CircleShape c(m_tic_dist.x/3.f);
            c.setPosition(m_offset.x + m_tic_dist.x/6.f , m_offset.y + m_tic_dist.y/6.f  );
            c.setOutlineColor(sf::Color::Blue);
            c.setOutlineThickness(2);
            //c.setFillColor(sf::Color::Blue);
            m_circles.push_back(c);
        }
        occupied[zone - 1] = true;
    }

    else if ( zone == Zones::TWO && !occupied[zone-1] )
    {
        if ( x_or_o == XO::X)
        {
            m_ticks[4].position = sf::Vector2f(m_offset.x + m_tic_dist.x, m_offset.y );
            m_ticks[5].position = sf::Vector2f(m_offset.x + (2.f*m_tic_dist.x), m_offset.y + m_tic_dist.y);

            m_ticks[6].position = sf::Vector2f(m_offset.x+(2.f*m_tic_dist.x), m_offset.y);
            m_ticks[7].position = sf::Vector2f(m_offset.x + m_tic_dist.x, m_offset.y + m_tic_dist.y);
            for(int i = 4; i < 8 ; ++i ) m_ticks[i].color = sf::Color::Blue;
        }
        else
        {
            sf::CircleShape c(m_tic_dist.x/3.f);
            c.setPosition(m_offset.x + 7.f*m_tic_dist.x/6.f , m_offset.y + m_tic_dist.y/6.f  );
            c.setOutlineColor(sf::Color::Blue);
            c.setOutlineThickness(2);
            //c.setFillColor(sf::Color::Blue);
            m_circles.push_back(c);
        }
        occupied[zone - 1] = true;
    }
    else if ( zone == Zones::THREE && !occupied[zone-1] )
    {
        if ( x_or_o == XO::X)
        {
            m_ticks[8].position = sf::Vector2f(m_offset.x + (2.f*m_tic_dist.x), m_offset.y );
            m_ticks[9].position = sf::Vector2f(m_offset.x + m_dims.x, m_offset.y + m_tic_dist.y);

            m_ticks[10].position = sf::Vector2f(m_offset.x+m_dims.x, m_offset.y);
            m_ticks[11].position = sf::Vector2f(m_offset.x + (2.f*m_tic_dist.x), m_offset.y + m_tic_dist.y);
            for(int i = 8; i < 12 ; ++i ) m_ticks[i].color = sf::Color::Blue;
        }
        else
        {
            sf::CircleShape c(m_tic_dist.x/3.f);
            c.setPosition(m_offset.x + 13.f*m_tic_dist.x/6.f , m_offset.y + m_tic_dist.y/6.f  );
            c.setOutlineColor(sf::Color::Blue);
            c.setOutlineThickness(2);
            //c.setFillColor(sf::Color::Blue);
            m_circles.push_back(c);
        }
        occupied[zone - 1] = true;
    }
    else if ( zone == Zones::FOUR && !occupied[zone-1] )
    {
        if ( x_or_o == XO::X)
        {
            m_ticks[12].position = sf::Vector2f(m_offset.x , m_offset.y + m_tic_dist.y );
            m_ticks[13].position = sf::Vector2f(m_offset.x + m_tic_dist.x, m_offset.y + (2.f*m_tic_dist.y));

            m_ticks[14].position = sf::Vector2f(m_offset.x + m_tic_dist.x, m_offset.y + m_tic_dist.y);
            m_ticks[15].position = sf::Vector2f(m_offset.x , m_offset.y + (2.f*m_tic_dist.y));
            for(int i = 12; i < 16 ; ++i ) m_ticks[i].color = sf::Color::Blue;
        }
        else
        {
            sf::CircleShape c(m_tic_dist.x/3.f);
            c.setPosition(m_offset.x + m_tic_dist.x/6.f , m_offset.y + 7.f*m_tic_dist.y/6.f  );
            c.setOutlineColor(sf::Color::Blue);
            c.setOutlineThickness(2);
            //c.setFillColor(sf::Color::Blue);
            m_circles.push_back(c);
        }
        occupied[zone - 1] = true;
    }
    else if ( zone == Zones::FIVE && !occupied[zone-1] )
    {
        if ( x_or_o == XO::X)
        {
            m_ticks[16].position = sf::Vector2f(m_offset.x+m_tic_dist.x , m_offset.y + m_tic_dist.y );
            m_ticks[17].position = sf::Vector2f(m_offset.x + (2.f*m_tic_dist.x), m_offset.y + (2.f*m_tic_dist.y));

            m_ticks[18].position = sf::Vector2f(m_offset.x + (2.f*m_tic_dist.x), m_offset.y + m_tic_dist.y);
            m_ticks[19].position = sf::Vector2f(m_offset.x + m_tic_dist.x , m_offset.y + (2.f*m_tic_dist.y));
            for(int i = 16; i < 20 ; ++i ) m_ticks[i].color = sf::Color::Blue;
        }
        else
        {
            sf::CircleShape c(m_tic_dist.x/3.f);
            c.setPosition(m_offset.x + 7.f*m_tic_dist.x/6.f , m_offset.y + 7.f*m_tic_dist.y/6.f  );
            c.setOutlineColor(sf::Color::Blue);
            c.setOutlineThickness(2);
            //c.setFillColor(sf::Color::Blue);
            m_circles.push_back(c);
        }
        occupied[zone - 1] = true;
    }
    else if ( zone == Zones::SIX && !occupied[zone-1] )
    {
        if ( x_or_o == XO::X)
        {
            m_ticks[20].position = sf::Vector2f(m_offset.x+(2.f*m_tic_dist.x) , m_offset.y + m_tic_dist.y );
            m_ticks[21].position = sf::Vector2f(m_offset.x + m_dims.x, m_offset.y + (2.f*m_tic_dist.y));

            m_ticks[22].position = sf::Vector2f(m_offset.x + m_dims.x, m_offset.y + m_tic_dist.y);
            m_ticks[23].position = sf::Vector2f(m_offset.x + (2.f*m_tic_dist.x) , m_offset.y + (2.f*m_tic_dist.y));
            for(int i = 20; i < 24 ; ++i ) m_ticks[i].color = sf::Color::Blue;
        }
        else
        {
            sf::CircleShape c(m_tic_dist.x/3.f);
            c.setPosition(m_offset.x + 13.f*m_tic_dist.x/6.f , m_offset.y + 7.f*m_tic_dist.y/6.f  );
            c.setOutlineColor(sf::Color::Blue);
            c.setOutlineThickness(2);
            //c.setFillColor(sf::Color::Blue);
            m_circles.push_back(c);
        }
        occupied[zone - 1] = true;
    }
}



Zones Board::inZone(const sf::Vector2f& mappedCoord )
{
    //auto gb = m_rect.getGlobalBounds();
    //float z1Boundx = (m_dims.x)/3.f;
    //float z1Boundy = (m_dims.y)/3.f;

    if ( mappedCoord.x <= m_offset.x+m_tic_dist.x && mappedCoord.y <= m_offset.y+m_tic_dist.y && mappedCoord.x >= m_offset.x && mappedCoord.y >= m_offset.y)
    {
         return Zones::ONE;
    }
    else if ( mappedCoord.x <= m_offset.x+(2.f*m_tic_dist.x) && mappedCoord.y <= m_offset.y+m_tic_dist.y && mappedCoord.x >= m_offset.x+m_tic_dist.x && mappedCoord.y >= m_offset.y)
    {
         return Zones::TWO;
    }
    else if ( mappedCoord.x <= m_offset.x+m_dims.x && mappedCoord.y <= m_offset.y+m_tic_dist.y && mappedCoord.x >= m_offset.x+(2.f*m_tic_dist.x) && mappedCoord.y >= m_offset.y)
    {
         return Zones::THREE;
    }
    else if ( mappedCoord.x <= m_offset.x+m_tic_dist.x && mappedCoord.y <= m_offset.y+(2.f*m_tic_dist.y) && mappedCoord.x >= m_offset.x && mappedCoord.y >= m_offset.y + m_tic_dist.y) 
    {
         return Zones::FOUR;
    }
    else if ( mappedCoord.x <= m_offset.x+(2.f*m_tic_dist.x) && mappedCoord.y <= m_offset.y+(2.f*m_tic_dist.y) && mappedCoord.x >= m_offset.x+m_tic_dist.x && mappedCoord.y >= m_offset.y + m_tic_dist.y) 
    {
         return Zones::FIVE;
    }
    else if ( mappedCoord.x <= m_offset.x+m_dims.x && mappedCoord.y <= m_offset.y+(2.f*m_tic_dist.y) && mappedCoord.x >= m_offset.x+(2.f*m_tic_dist.x) && mappedCoord.y >= m_offset.y + m_tic_dist.y) 
    {
         return Zones::SIX;
    }
    else if ( mappedCoord.x <= m_offset.x+m_tic_dist.x && mappedCoord.y <= m_offset.y+m_dims.y && mappedCoord.x >= m_offset.x && mappedCoord.y >= m_offset.y + (2.f*m_tic_dist.y)) 
    {
         return Zones::SEVEN;
    }
    else if ( mappedCoord.x <= m_offset.x+(2.f*m_tic_dist.x) && mappedCoord.y <= m_offset.y+m_dims.y && mappedCoord.x >= m_offset.x+m_tic_dist.x && mappedCoord.y >= m_offset.y + (2.f*m_tic_dist.y)) 
    {
         return Zones::EIGHT;
    }
    else if ( mappedCoord.x <= m_offset.x+m_dims.x && mappedCoord.y <= m_offset.y+m_dims.y && mappedCoord.x >= m_offset.x+(2.f*m_tic_dist.x) && mappedCoord.y >= m_offset.y + (2.f*m_tic_dist.y)) 
    {
         return Zones::NINE;
    }
    else
    {
        return Zones::OUT;
    }
}

void Board::reSized(float x, float y)
{
    //float w = 2.f*x/3.f;
    //float h = 2.f*y/3.f;


    //float offset_x = x/6.f;
    //float offset_y = y/6.f;
    //m_rect = sf::RectangleShape(sf::Vector2f(w,h)); 
    //m_rect.setPosition(offset_x, offset_y);
    //m_rect.setSize( {2.f*x/3.f, 2.f*y/3.f});
    //m_rect.setPosition(x/6.f, y/6.f);
    //m_rect = sf::RectangleShape({x*2.f/3.f,y*2.f/3.f}); 
    //m_rect.setPosition( x/6.f, y/6.f);
}
