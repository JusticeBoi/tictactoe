#include <SFML/Graphics.hpp>
#include <iostream>
//#include "../lib/inc/Board.hpp"
//#include "../lib/inc/BoardCell.hpp"
#include "../lib/inc/Game.hpp"

int main()
{
    Game game;
    game.start();

    //float width = 800.f;
    //float height = 800.f;
    //sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
    //Board b({width,height});
    //std::cout <<"size of board : " << sizeof(Board) <<'\n';
    //Cell c;
    //BoardCell bc;
    ////sf::RectangleShape rect({width*2.f/3.f,height*2.f/3.f});
    ////rect.setFillColor(sf::Color::White);
    ////rect.move( width/6.f, width/6.f);
    ////sf::RectangleShape line({width*2.f/3.f, 2.5f});
    ////line.rotate(90.f);
    ////line.setFillColor(sf::Color::Black);
    ////line.move( 7.f*width/18.f, width/6.f);
    ////sf::VertexArray lines(sf::Lines, 4);
    ////lines[0].position = sf::Vector2f(10, 0);
    ////lines[1].position = sf::Vector2f(20, 0);
    ////lines[2].position = sf::Vector2f(30, 5);
    ////lines[3].position = sf::Vector2f(40, 2);

    //while (window.isOpen())
    //{
    //    sf::Event event;
    //    while (window.pollEvent(event))
    //    {
    //        switch(event.type)
    //        {
    //            case sf::Event::Closed:
    //                window.close();
    //                break;
    //            case sf::Event::MouseButtonPressed:
    //                if (event.mouseButton.button == sf::Mouse::Right)
    //                {
    //                    std::cout << "the right button was pressed" << std::endl;
    //                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
    //                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
    //                }
    //                else if (event.mouseButton.button == sf::Mouse::Left)
    //                {
    //                    auto a = sf::Mouse::getPosition(window);
    //                    //std::cout << "the right button was pressed" << std::endl;
    //                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
    //                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
    //                    sf::Vector2f mapped = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
    //                    std::cout << "mapped x: " << mapped.x << std::endl;
    //                    std::cout << "mapped y: " << mapped.y << std::endl;
    //                    //c.setPosition(mapped.x, mapped.y);


    //                    //std::cout << "mouse x: " << a.x << std::endl;
    //                    //std::cout << "mouse y: " << a.y << std::endl;
    //                    //sf::FloatRect gb = b.m_rect.getGlobalBounds();
    //                    //std::cout <<" gb width " << gb.width << " gb height : "<< gb.height <<'\n';
    //                    //std::cout <<" gb top " << gb.top << " gb left : "<< gb.left <<'\n';
    //                    //std::cout <<" am i inside rect? : " << b.contains(mapped)<<'\n';
    //                    //std::cout <<" am i inside zone? : " << static_cast<int>(b.inZone(mapped))<<'\n';
    //                    //b.drawMoveIn(b.inZone(mapped),XO::O);

    //                   

    //                }
    //                break;
    //            case sf::Event::Resized:
    //                //width = event.size.width;
    //                //height = event.size.height;
    //                //rect = sf::RectangleShape({width*2.f/3.f,height*2.f/3.f}); 
    //                //rect.setPosition( width/6.f, height/6.f);
    //                std::cout << "new width: " << width << std::endl;
    //                std::cout << "new height: " << height << std::endl;
    //                break;

    //        }

    //    }

    //    window.clear();
    //    //window.draw(rect);
    //    //window.draw(line);
    //    //window.draw(b);
    //    //window.draw(c);
    //    window.draw(bc);
    //    window.display();
    //}

    return 0;
}
