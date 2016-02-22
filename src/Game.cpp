#include <Game.h>

Game::Game()
{
	m_Car = Car(myVector(2075, 65), myVector(0, 0), 0.3, myVector(0, 0)); // Creates players car with default paramaters
	TexLoader.load();
	generateMap(TexLoader.getTextureIterator(2));
	m_Car.setCarTexture(TexLoader.getTextureIterator(3));
	m_Spedo.SetRPMTexture(TexLoader.getTextureIterator(0));
	m_Spedo.setupCheckpoints();
}

void Game::draw(RenderTarget & target, RenderStates states) const 
{
	target.draw(MapSprite);
	target.draw(m_Car);  // Draws car to screen

	for (int i = 0; i < Tyres.size(); i++) // Draws all tyres in vector of tyres
	{
		target.draw(*Tyres.at(i));
	}
}

void Game::update(float timestep)
{
	m_Car.update(timestep); // Passes car timestep for update
	for (int i = 0; i < Tyres.size(); i++) // Draws all tyres in vector of tyres
	{
		Tyres.at(i)->update(timestep);
	}
	m_Spedo.updateNeedle(m_Car.m_iRPM);
	m_Spedo.updateGear(m_Car.m_iGear);

	for (int i = 0; i < Tyres.size(); i++) // Ssets up out collisions
	{
		m_Car.Collide(Tyres.at(i)); // Car collides with all tyres
		for (int j = 0; j < Tyres.size(); j++)
		{
			if (i != j) // Stops tyres from colliding with themselves
			{
				Tyres.at(i)->Collide(Tyres.at(j));
			}
		}

	}
	m_Spedo.updateTimers();

	// Restarts laptime and sets new best time if player has beaten previous best time
	if (m_Spedo.StartLine.intersects(m_Car.m_render.getGlobalBounds()))
	{
		if (MidPassed == true)
		{
			m_Spedo.UpdateBestTime();
		}
		m_Spedo.ResetTimer();
		MidPassed = false;
	}

	if (m_Spedo.MidLine.intersects(m_Car.m_render.getGlobalBounds()))
	{
		MidPassed = true;
	}

}

void Game::processKeyPress(Keyboard::Key code)
{
	if (code == Keyboard::W || code == Keyboard::Up) // If 'W' or 'Up' pressed then accelerate
	{
		m_Car.m_iGear = 1;
	}

	if (code == Keyboard::D || code == Keyboard::Right) // If 'D' or 'Right' pressed then rotate clockwise
	{
		m_Car.RotatingRight = true;
		m_Car.RotatingLeft = false;
	}

	if (code == Keyboard::A || code == Keyboard::Left) //If 'A' or 'Left' pressed then rotate anti-clockwise
	{
		m_Car.RotatingRight = false;
		m_Car.RotatingLeft = true;
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
		m_Car.RotatingRight = false;
		m_Car.RotatingLeft = false;
	}

	if (code == Keyboard::A || code == Keyboard::Left) // Stops turning car after 'A' or 'Left' release
	{
		m_Car.RotatingRight = false;
		m_Car.RotatingLeft = false;
	}

	if (code == Keyboard::S || code == Keyboard::Down) //If 'A' or 'Down' key released then enter neutral
	{
		m_Car.m_iGear = 0;
	}
}

void Game::generateMap(vector<Texture>::iterator GivenTexture)
{
	MapSprite.setTexture(*GivenTexture);

	MapSprite.setPosition(0, -360); // Centers Map

	MapSprite.setScale(1, 1);
}

Vector2f Game::GetCarPos()
{
	return Vector2f(m_Car.ReturnCarPos());
}

Vector2f Game::GetRPMCounterPos()
{
	return m_Spedo.getRPMCounterPos();
}

void Game::CreateTyre(Vector2f Position)
{
	//Tyre1 = Tyre(myVector::ConvertToMyVector(Position), 0.1);
	//Tyre1.TyreSprite.setPosition(Position);

	Tyres.push_back(new Tyre(myVector::ConvertToMyVector(Position), 0.1));
	Tyres.back()->setTyreTexture(TexLoader.getTextureIterator(1));
	saveTyrePosToFile();
}

void Game::saveTyrePosToFile()
{
	//Open file
	ofstream file;
	file.open("..\\assets\\Maps\\tyrepos.txt");

	//Write to file;
	for (int i = 0; i < Tyres.size(); i++)
	{
		file << Tyres.at(i)->m_position.x() << " " << Tyres.at(i)->m_position.y() << endl;
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
			Tyres.push_back(new Tyre(myVector(fX,fY), 0.1));
			Tyres.back()->setTyreTexture(TexLoader.getTextureIterator(1));
		}
	}

	fileHandle.close();
}