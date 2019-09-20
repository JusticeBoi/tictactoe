#include "../inc/Game.hpp"





void Game::start()
{
    sf::RenderWindow w_(sf::VideoMode(800.f, 800.f), "Tic Tac Toe"); 
    turn_ = Turn::Human;


    while (w_.isOpen())
    {
        sf::Event event;
        while (w_.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    w_.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        std::cout << "the right button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    }
                    else if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        //std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        //std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                        sf::Vector2f mapped = w_.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                        std::cout << "mapped x: " << mapped.x << std::endl;
                        std::cout << "mapped y: " << mapped.y << std::endl;
                        Zone clickedZone = bc_.clickedZone(mapped);
                        if ( clickedZone != Zone::OUT )
                        {
                            if ( turn_ == Turn::Human )
                            {
                                if (bc_.fillZoneWith(clickedZone, XO::X )) turn_ = Turn::Machine;
                            }
                            else
                            {
                                if (bc_.fillZoneWith(clickedZone, XO::O )) turn_ = Turn::Human;
                            }
                            State s = isFinito();
                            if ( s != Game::State::NotFinished)
                            {
                                std::string win_msg = ( s == State::XWon ) ? "X won " : "O won";
                                std::cout << win_msg <<'\n';
                                w_.close();
                                
                            }

                        }
                        std::cout <<"clicked zone : " << bc_.clickedZone(mapped) << '\n';

                    }
                    break;
            }

        }

        w_.clear();
        w_.draw(bc_);
        w_.display();
    }
}


Game::State Game::isFinito() const 
{
    XO won = bc_.hasWOn();
    if ( won != XO::None ) return ( won == XO::X ) ? Game::State::XWon : Game::State::OWon;  
    else return Game::State::NotFinished;
}
