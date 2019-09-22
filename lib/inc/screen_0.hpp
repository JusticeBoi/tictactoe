#include <iostream>
#include "cScreen.hpp"

#include <SFML/Graphics.hpp>

class screen_0 : public cScreen
{
private:
	int alpha_max;
	int alpha_div;
	bool playing;
public:
	screen_0(void);
	virtual int Run(sf::RenderWindow &App);
};

screen_0::screen_0(void)
{
	alpha_max = 3 * 255;
	alpha_div = 3;
	playing = false;
}
int screen_0::Run(sf::RenderWindow &App)
{
	sf::Event Event;
	bool Running = true;
	sf::Texture Texture;
	sf::Sprite Sprite;
	int alpha = 0;
	sf::Font Font;
	sf::Text PlayTwoPlayer;
	sf::Text PlayVsAI;
	sf::Text Exit;
	sf::Text Menu3;
	int menu = 0;

	if (!Texture.loadFromFile("Linux.jpg"))
	{
		std::cerr << "Error loading presentation.gif" << std::endl;
		return (-1);
	}
	Sprite.setTexture(Texture);
	Sprite.setColor(sf::Color(255, 255, 255, alpha));
	if (!Font.loadFromFile("../fonts/Inconsolata.ttf"))
	{
		std::cerr << "Error loading Inconsolata.ttf" << std::endl;
		return (-1);
	}
	PlayTwoPlayer.setFont(Font);
	PlayTwoPlayer.setCharacterSize(20);
	PlayTwoPlayer.setString("Human vs Human");
	PlayTwoPlayer.setPosition({ 250.f, 150.f });

	PlayVsAI.setFont(Font);
	PlayVsAI.setCharacterSize(20);
	PlayVsAI.setString("Human vs Computer");
	PlayVsAI.setPosition({ 250.f, 210.f });


	Exit.setFont(Font);
	Exit.setCharacterSize(20);
	Exit.setString("Exit");
	Exit.setPosition({ 250.f, 270.f });

	Menu3.setFont(Font);
	Menu3.setCharacterSize(20);
	Menu3.setString("Continue");
	Menu3.setPosition({ 250.f, 150.f });

	if (playing)
	{
		alpha = alpha_max;
	}

	while (Running)
	{
		//Verifying events
		while (App.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return (-1);
			}
            if ( Event.type == sf::Event::MouseButtonPressed )
            {
                if ( Event.mouseButton.button == sf::Mouse::Left  )
                {
                    sf::Vector2f mapped = App.mapPixelToCoords({Event.mouseButton.x, Event.mouseButton.y});
                    if ( Exit.getGlobalBounds().contains(mapped))
                    {
                        menu = 1;
						return (-1);
                    }
                    if ( playing )
                    {
                        if ( Menu3.getGlobalBounds().contains(mapped) )
                        {
                            std::cout <<"pressed mouse over start" <<'\n';
                            menu = 0;
					    	playing = true;
                            return 1;
                        }
                    }
                    else if ( PlayTwoPlayer.getGlobalBounds().contains(mapped) ) 
                    {
                            std::cout <<"pressed mouse over start" <<'\n';
                            menu = 0;
					    	playing = true;
                            return 1;
                    }
                    else if ( PlayVsAI.getGlobalBounds().contains(mapped) ) 
                    {
                            std::cout <<"pressed mouse over start" <<'\n';
                            menu = 0;
					    	playing = true;
                            return 1;
                    }
                }
            }
			//Key pressed
			if (Event.type == sf::Event::KeyPressed)
			{
				switch (Event.key.code)
				{
				case sf::Keyboard::Up:
					menu = 0;
					break;
				case sf::Keyboard::Down:
					menu = 1;
					break;
				case sf::Keyboard::Return:
					if (menu == 0)
					{
						//Let's get play !
						playing = true;
						return (1);
					}
					else
					{
						//Let's get work...
						return (-1);
					}
					break;
				default:
					break;
				}
			}
		}
		//When getting at alpha_max, we stop modifying the sprite
		if (alpha<alpha_max)
		{
			alpha++;
		}
		Sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));
		//if (menu == 0)
		//{
		//	Menu1.setColor(sf::Color(255, 0, 0, 255));
		//	Menu2.setColor(sf::Color(255, 255, 255, 255));
		//	Menu3.setColor(sf::Color(255, 0, 0, 255));
		//}
		//else
		//{
		//	Menu1.setColor(sf::Color(255, 255, 255, 255));
		//	Menu2.setColor(sf::Color(255, 0, 0, 255));
		//	Menu3.setColor(sf::Color(255, 255, 255, 255));
		//}

		//Clearing screen
		App.clear();
		//Drawing
		App.draw(Sprite);
		if (alpha == alpha_max)
		{
			if (playing)
			{
				App.draw(Menu3);
			}
			else
			{
				App.draw(PlayTwoPlayer);
				App.draw(PlayVsAI);
			}
			App.draw(Exit);
		}
		App.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return (-1);
}
