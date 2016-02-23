#include <Game.h>

Game::Game()
{
	m_Car = Car(myVector(2075, 65), myVector(0, 0), 0.3, myVector(0, 0)); // Creates players car with default paramaters
	m_TexLoader.load();
	generateMap(m_TexLoader.getTextureIterator(2));
	m_Car.setCarTexture(m_TexLoader.getTextureIterator(3));
	m_HUD.setRPMTexture(m_TexLoader.getTextureIterator(0));
}

void Game::draw(RenderTarget & target, RenderStates states) const 
{
	target.draw(m_MapSprite);
	target.draw(m_Car);  // Draws car to screen

	for (int i = 0; i < m_Tyres.size(); i++) // Draws all m_Tyres in vector of m_Tyres
	{
		target.draw(*m_Tyres.at(i));
	}
}

void Game::update(float timestep)
{
	m_Car.update(timestep); // Passes car timestep for update
	for (int i = 0; i < m_Tyres.size(); i++) // Draws all m_Tyres in vector of m_Tyres
	{
		m_Tyres.at(i)->update(timestep);
	}
	m_HUD.updateNeedle(m_Car.m_iRPM);
	m_HUD.updateGear(m_Car.m_iGear);

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
	m_HUD.updateTimers();

	// Restarts laptime and sets new best time if player has beaten previous best time
	if (m_HUD.m_StartLine.intersects(m_Car.m_render.getGlobalBounds()))
	{
		if (m_bMidPassed == true)
		{
			m_HUD.updateBestTime();
		}
		m_HUD.resetTimer();
		m_bMidPassed = false;
	}

	if (m_HUD.m_MidLine.intersects(m_Car.m_render.getGlobalBounds()))
	{
		m_bMidPassed = true;
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
}

void Game::generateMap(vector<Texture>::iterator GivenTexture)
{
	m_MapSprite.setTexture(*GivenTexture);

	m_MapSprite.setPosition(0, -360); // Centers Map

	m_MapSprite.setScale(1, 1);
}

Vector2f Game::getCarPos()
{
	return Vector2f(m_Car.ReturnCarPos());
}

Vector2f Game::getRPMCounterPos()
{
	return m_HUD.getRPMCounterPos();
}

void Game::createTyre(Vector2f Position)
{
	//Tyre1 = Tyre(myVector::ConvertToMyVector(Position), 0.1);
	//Tyre1.m_Tyresprite.setPosition(Position);

	m_Tyres.push_back(new Tyre(myVector::ConvertToMyVector(Position), 0.1));
	m_Tyres.back()->setTyreTexture(m_TexLoader.getTextureIterator(1));
	saveTyrePosToFile();
}

void Game::saveTyrePosToFile()
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

void Game::loadTyrePosFromFile()
{
	ifstream fileHandle;
	string sLineFromFile;

	float fX;
	float fY;

	fileHandle.open("..\\assets\\Maps\\tyrepos.txt");
	if (fileHandle.is_open())
	{
		while (fileHandle >> fX >> fY)
		{
			m_Tyres.push_back(new Tyre(myVector(fX,fY), 0.1));
			m_Tyres.back()->setTyreTexture(m_TexLoader.getTextureIterator(1));
		}
	}

	fileHandle.close();
}