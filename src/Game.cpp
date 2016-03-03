#include <Game.h>

Game::Game()
{
	m_Car = Car(myVector(2075, 65), myVector(0, 0), 0.3, myVector(0, 0)); // Creates players car with default paramaters
	m_TexLoader.load(); // Loads in all textures
	generateMap(m_TexLoader.getTextureIterator(2)); // Assigns correct texture to map
	m_Car.setCarTexture(m_TexLoader.getTextureIterator(3)); // Assigns correct texture to Car
	m_HUD.setRPMTexture(m_TexLoader.getTextureIterator(0)); // Assigns correct texture to RPM counter
}

void Game::draw(RenderTarget & target, RenderStates states) const 
{
	target.draw(m_MapSprite); // Draw map
	target.draw(m_Car);  // Draws car to screen

	for (int i = 0; i < m_Tyres.size(); i++) // Draws all m_Tyres in vector of m_Tyres
	{
		target.draw(*m_Tyres.at(i));
	}
}

void Game::update(float timestep)
{
	m_Car.update(timestep); // Passes car timestep for update
	for (int i = 0; i < m_Tyres.size(); i++) // Allows updating for all tyres
	{
		m_Tyres.at(i)->update(timestep);
	}
	m_HUD.updateNeedle(m_Car.m_iRPM); // Updates needle for RPM counter
	m_HUD.updateGear(m_Car.m_iGear); // Updates gear for HUD

	for (int i = 0; i < m_Tyres.size(); i++) // Ssets up out collisions
	{
		m_Car.Collide(m_Tyres.at(i)); // Car collides with all m_Tyres
		for (int j = 0; j < m_Tyres.size(); j++)
		{
			if (i != j) // Stops m_Tyres from colliding with themselves
			{
				m_Tyres.at(i)->Collide(m_Tyres.at(j));
			}
		}

	}
	m_HUD.updateTimers(); // Updates timers for HUD

	// Restarts laptime and sets new best time if player has beaten previous best time
	if (m_HUD.m_StartLine.intersects(m_Car.m_render.getGlobalBounds()))
	{
		if (m_bMidPassed == true) // If player has reached midpoint then returned to start point
		{
			m_HUD.updateBestTime();// Update best time
		}
		m_HUD.resetTimer();
		m_bMidPassed = false; // Reset mid point check
	}

	if (m_HUD.m_MidLine.intersects(m_Car.m_render.getGlobalBounds())) // If player has reached midline checkpoint
	{
		m_bMidPassed = true; // Set pass bool to true
	}

}

void Game::processKeyPress(Keyboard::Key code)
{
	if (code == Keyboard::W || code == Keyboard::Up) // If 'W' or 'Up' pressed then accelerate
	{
		if (m_Car.m_iGear <= 0)
		{
			m_Car.m_iGear = 1;
		}
	}

	if (code == Keyboard::D || code == Keyboard::Right) // If 'D' or 'Right' pressed then rotate clockwise
	{
		m_Car.m_bRotatingRight = true;
		m_Car.m_bRotatingLeft = false;
	}

	if (code == Keyboard::A || code == Keyboard::Left) //If 'A' or 'Left' pressed then rotate anti-clockwise
	{
		m_Car.m_bRotatingRight = false;
		m_Car.m_bRotatingLeft = true;
	}

	if (code == Keyboard::S || code == Keyboard::Down) // If 'S' or 'Down' pressed then reverse
	{
		m_Car.m_iGear = -1;
	}
}

void Game::processKeyRelease(Keyboard::Key code)
{
	if (code == Keyboard::W || code == Keyboard::Up) // If 'W' or ' Up' released the slowly decrease velocity
	{
		m_Car.m_iGear = 0;
	}

	if (code == Keyboard::D || code == Keyboard::Right) // Stops turning car after 'D' or 'Right' key release
	{
		m_Car.m_bRotatingRight = false;
		m_Car.m_bRotatingLeft = false;
	}

	if (code == Keyboard::A || code == Keyboard::Left) // Stops turning car after 'A' or 'Left' release
	{
		m_Car.m_bRotatingRight = false;
		m_Car.m_bRotatingLeft = false;
	}

	if (code == Keyboard::S || code == Keyboard::Down) //If 'A' or 'Down' key released then enter neutral
	{
		m_Car.m_iGear = 0;
	}
	if (code == Keyboard::Return) //If enter is pressed then save all tyre positions to file
	{
		saveTyrePosToFile();
	}

	if (code == Keyboard::BackSpace) // Load tyres positions from file
	{
		loadTyrePosFromFile();
	}
	
}

void Game::generateMap(vector<Texture>::iterator GivenTexture)
{
	m_MapSprite.setTexture(*GivenTexture);

	m_MapSprite.setPosition(0, -360); // Centers Map

	m_MapSprite.setScale(1, 1);
}

Vector2f Game::getCarPos() // Returns car position
{
	return Vector2f(m_Car.ReturnCarPos());
}

Vector2f Game::getRPMCounterPos() // Returns RPM position
{
	return m_HUD.getRPMCounterPos();
}

void Game::createTyre(Vector2f Position) // Creates a tyre with the given position
{
	m_Tyres.push_back(new Tyre(myVector::ConvertToMyVector(Position), 0.1));
	m_Tyres.back()->setTyreTexture(m_TexLoader.getTextureIterator(1)); // Assigns texture to tyre
}

void Game::saveTyrePosToFile() // Saves all tyres to a file
{
	//Open file
	ofstream file;
	file.open("..\\assets\\Maps\\tyrepos.txt");

	//Write to file;
	for (int i = 0; i < m_Tyres.size(); i++)
	{
		file << m_Tyres.at(i)->m_position.x() << " " << m_Tyres.at(i)->m_position.y() << endl;
	}
	//Close file
	file.close();
}

void Game::loadTyrePosFromFile() // Loads all tyres from a file
{
	ifstream fileHandle;
	string sLineFromFile;

	float fX;
	float fY;

	//Open file
	fileHandle.open("..\\assets\\Maps\\tyrepos.txt");
	if (fileHandle.is_open())
	{
		while (fileHandle >> fX >> fY) // While 2 floats with a space inbetween exist on each line
		{
			m_Tyres.push_back(new Tyre(myVector(fX,fY), 0.1)); // Pushback new tyre with these X,Y positions
			m_Tyres.back()->setTyreTexture(m_TexLoader.getTextureIterator(1));// Set tyre texture
		}
	}
	// Close file
	fileHandle.close();
}