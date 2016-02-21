#include <iostream>
#include <SFML/Graphics.hpp>

#include <Game.h>

using namespace sf;
using namespace std;

int main()
{
	RenderWindow window(VideoMode(1000, 800), "Racing Game");
	window.setFramerateLimit(60);
	
	Game game; // Game object

	Clock clock; // Game time clock

	View gameview;
	View miniMap;
	View RPMCounter;

	// Sets minimap to be distant away from gameview
	miniMap.zoom(4);
	// Makes gameview use the entire window screen
	gameview.setSize(Vector2f(window.getSize()));
	RPMCounter.setSize(Vector2f(window.getSize()));

	game.loadTyrePosFromFile();
			
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// Closes window if close button clicked
			if (event.type == Event::Closed)
			{
				window.close(); // Allows window to close when 'X' is pressed
				return 0;
			}
			// Records key presses and sends them to game class to be processed
			if (event.type == Event::KeyPressed)
			{
				game.processKeyPress(event.key.code); // Detects key pressess
			}
			if (event.type == Event::KeyReleased)
			{
				game.processKeyRelease(event.key.code); // Dectects key releases
			}
			if (event.type == Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == Mouse::Left) // Allows tyres to be placed by clicking on the map
				{
					//game.CreateTyre(window.mapPixelToCoords(Mouse::getPosition(window),gameview));
					//cout << window.mapPixelToCoords(Mouse::getPosition(window)).x << "    " << window.mapPixelToCoords(Mouse::getPosition(window)).y << endl;
					//cout << Mouse::getPosition().x << "    " << Mouse::getPosition().y << endl;
				}
			}
		
		}
		//Gets the elasped time during the frame
		if (clock.getElapsedTime().asSeconds() > 0.005)
		{
			game.update(clock.getElapsedTime().asSeconds());
			gameview.setCenter(game.GetCarPos());
			miniMap.setViewport(FloatRect(0.75f, 0, 0.25f, 0.25f));
			miniMap.setCenter(2000,1600);
			//RPMCounter.setViewport(FloatRect(0.6f, 0.6f, 1.f, 1.f));
			RPMCounter.setCenter(game.GetRPMCounterPos().x - 200, game.GetRPMCounterPos().y - 100);
			clock.restart();
		}

		//Draws gameview
		window.setView(gameview);
		window.clear(Color::Black);
		window.draw(game);

		//Draws minimap
		window.setView(miniMap);
		window.draw(game);

		//Draws RPM counter
		window.setView(RPMCounter);
		window.draw(game.m_Spedo);

		window.display();
	}

}