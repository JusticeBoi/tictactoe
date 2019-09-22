#include "../inc/MenuScreen.hpp"

MenuScreen::MenuScreen()
{
	alpha_max = 3 * 255;
	alpha_div = 3;
	playing = NowPlaying::NOTHING;
	wasPlaying = NowPlaying::NOTHING;
}
int MenuScreen::Run(sf::RenderWindow &App)
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
	sf::Text Continue;
	int menu = 0;

	if (!Texture.loadFromFile("../themes/spiral.jpg"))
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
	PlayTwoPlayer.setCharacterSize(40);
	PlayTwoPlayer.setString("Human vs Human");
	PlayTwoPlayer.setPosition({ 250.f, 230.f });

	PlayVsAI.setFont(Font);
	PlayVsAI.setCharacterSize(40);
	PlayVsAI.setString("Human vs Computer");
	PlayVsAI.setPosition({ 250.f, 290.f });


	Exit.setFont(Font);
	Exit.setCharacterSize(40);
	Exit.setString("Exit");
	Exit.setPosition({ 250.f, 350.f });

	Continue.setFont(Font);
	Continue.setCharacterSize(40);
	Continue.setString("Continue");
	Continue.setPosition({ 250.f, 230.f });
    Hover hover  = Hover::OUT; 

	if (playing != NowPlaying::NOTHING)
	{
		alpha = alpha_max;
	}

	while (Running)
	{
		//Verifying events
		while (App.pollEvent(Event))
		{
            switch (Event.type )
            {
                case sf::Event::Closed: 
                    return -1;
                case sf::Event::MouseButtonPressed:
                    {
                        if ( Event.mouseButton.button == sf::Mouse::Left  )
                        {
                            sf::Vector2f mapped = App.mapPixelToCoords({Event.mouseButton.x, Event.mouseButton.y});
                            if ( Exit.getGlobalBounds().contains(mapped))
                            {
                                menu = 1;
				        		return -1;
                            }
                            if ( playing != NowPlaying::NOTHING )
                            {
                                if ( Continue.getGlobalBounds().contains(mapped) )
                                {
                                    menu = 0;
				        	    	playing = wasPlaying;
                                    return playing;
                                }
                            }
                            else if ( PlayTwoPlayer.getGlobalBounds().contains(mapped) ) 
                            {
                                    menu = 0;
				        	    	playing = NowPlaying::PVSP;
                                    wasPlaying = playing;
                                    return 1;
                            }
                            else if ( PlayVsAI.getGlobalBounds().contains(mapped) ) 
                            {
                                    menu = 0;
				        	    	playing = NowPlaying::PVSAI;
                                    wasPlaying = playing;
                                    return 2;
                            }
                        }
                        break;
                    }
                case sf::Event::MouseMoved:
                    {
                        sf::Vector2f mapped = App.mapPixelToCoords({Event.mouseMove.x, Event.mouseMove.y});
                        if ( Exit.getGlobalBounds().contains(mapped) ) { hover = Hover::EXIT;}  
                        else if ( playing == NowPlaying::NOTHING )
                        {
                            if ( PlayTwoPlayer.getGlobalBounds().contains(mapped) ) {hover = Hover::PTOP;} 
                            else if ( PlayVsAI.getGlobalBounds().contains(mapped) ){hover = Hover::PTOAI;} 
                        }
                        else if ( Continue.getGlobalBounds().contains(mapped) )
                        {
                            hover = Hover::CONTINUE;
                        }
                        else hover = Hover::OUT;

                        break;
                    }
                default:
                    break;
            }
		}
		//When getting at alpha_max, we stop modifying the sprite
		if (alpha<alpha_max)
		{
			++alpha;
		}
		Sprite.setColor(sf::Color(255, 255, 255, alpha / alpha_div));
        switch ( hover )
        {
            case Hover::EXIT:
            {
			    PlayTwoPlayer.setFillColor(sf::Color(255, 255, 255, 255));
			    PlayVsAI.setFillColor(sf::Color(255, 255, 255, 255));
			    Continue.setFillColor(sf::Color(255, 255, 255, 255));
			    Exit.setFillColor(sf::Color(255, 0, 0, 255));
                break;
            }
            case Hover::PTOP:
            {
			    PlayTwoPlayer.setFillColor(sf::Color(255, 0, 0, 255));
			    PlayVsAI.setFillColor(sf::Color(255, 255, 255, 255));
			    Continue.setFillColor(sf::Color(255, 255, 255, 255));
			    Exit.setFillColor(sf::Color(255, 255, 255, 255));
                break;
            }
            case Hover::PTOAI:
            {
			    PlayTwoPlayer.setFillColor(sf::Color(255, 255, 255, 255));
			    PlayVsAI.setFillColor(sf::Color(255, 0, 0, 255));
			    Continue.setFillColor(sf::Color(255, 255, 255, 255));
			    Exit.setFillColor(sf::Color(255, 255, 255, 255));
                break;
            }
            case Hover::CONTINUE:
            {
			    PlayTwoPlayer.setFillColor(sf::Color(255, 255, 255, 255));
			    PlayVsAI.setFillColor(sf::Color(255, 255, 255, 255));
			    Continue.setFillColor(sf::Color(255, 0 , 0, 255));
			    Exit.setFillColor(sf::Color(255, 255, 255, 255));
                break;
            }
            case Hover::OUT:
            {
			    PlayTwoPlayer.setFillColor(sf::Color(255, 255, 255, 255));
			    PlayVsAI.setFillColor(sf::Color(255, 255, 255, 255));
			    Continue.setFillColor(sf::Color(255, 255 , 255, 255));
			    Exit.setFillColor(sf::Color(255, 255, 255, 255));
                break;
            }
        }
		//Clearing screen
		App.clear();
		//Drawing
		App.draw(Sprite);
		if (alpha == alpha_max)
		{
			if (playing)
			{
				App.draw(Continue);
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

