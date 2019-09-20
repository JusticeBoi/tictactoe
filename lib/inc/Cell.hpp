#ifndef CELL__HPP_DEFINED
#define CELL__HPP_DEFINED

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

enum Zone : int
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

enum class XO: short
{
    X = 0,
    O = 1,
    None = -1
};


class Cell : public sf::Drawable
{
    public:
        Cell();
        bool contains(const sf::Vector2f& v) const ;

        static constexpr float width = 1600.f/9.f;
        static constexpr float height = 1600.f/9.f;
        static constexpr float borderThickness = 1.f;

        static constexpr float textXOffsetX = 33.f;
        static constexpr float textYOffsetX = -28.f;

        static constexpr float textXOffsetO = 18.f;
        static constexpr float textYOffsetO = -27.f;


        void setXO(XO x_or_o);
        XO getXO();
        void draw(sf::RenderTarget& target, sf::RenderStates /*states*/) const override  ;
        void setPosition(const sf::Vector2f& p );
        void setPosition(float x, float y );
        const sf::Vector2f& getPosition( ) const;
        void setFont(const sf::Font& sf);
        void setZone(Zone z);
        Zone getZone() const;
        XO getXO() const;

    private:
        XO xo_;
        sf::RectangleShape rec_;
        sf::Text symbol_;
        sf::Font font_;
        Zone z_;

};

#endif // CELL__HPP_DEFINED

