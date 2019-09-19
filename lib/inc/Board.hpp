#ifndef BOARD__HPP_DEFINED
#define BOARD__HPP_DEFINED

#include <SFML/Graphics.hpp>


enum Zones : int
{
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    OUT = 0
};
enum class XO: bool
{
    X = true,
    O = false
};

class Board : public sf::Drawable, public sf::Transformable
{
public:

    // add functions to play with the entity's geometry / colors / texturing...
    Board(const sf::Vector2f & size = sf::Vector2f(0, 0));
    bool contains(const sf::Vector2f& v2);
    void reSized(float x, float y);
    sf::RectangleShape m_rect;
    Zones inZone(const sf::Vector2f& mappedCoord );
    void drawMoveIn(Zones zone, XO x_or_o);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the entity's transform -- combine it with the one that was passed by the caller
        states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

        // apply the texture
        states.texture = &m_texture;

        // you may also override states.shader or states.blendMode if you want

        // draw the vertex array
        target.draw(m_rect, states);
        target.draw(m_lines, states);
        target.draw(m_ticks, states);
        for(auto&circle : m_circles ) target.draw(circle, states );
    }

    std::vector<sf::CircleShape> m_circles;
    sf::VertexArray m_lines;
    sf::VertexArray m_ticks;
    sf::Texture m_texture;
    sf::Vector2f m_offset;
    sf::Vector2f m_dims;
    sf::Vector2f m_tic_dist;
    bool occupied[9];

};


#endif //BOARD__HPP_DEFINED
