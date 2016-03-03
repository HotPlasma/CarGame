#include <HUD.h>
#include <Car.h>

HUD::HUD()
{
	m_RPMSprite.setPosition(721, 518); // Sets RPM counter to bottom left corner

	m_RPMSprite.setOrigin(m_RPMSprite.getLocalBounds().width / 2, m_RPMSprite.getLocalBounds().height / 2); // Sets origin to the centre
	m_RPMSprite.setScale(1, 1);

	//Create needle and set position within centre of RPM counter
	m_needle.setFillColor(Color::Green);
	m_needle.setSize(Vector2f(80, 10));
	m_needle.setPosition(1000-140, 800-140);
	m_needle.setOrigin(Vector2f(m_needle.getSize().x / 2 - 40, m_needle.getSize().y / 2));

	if (!DigiFont.loadFromFile("..\\assets\\HUD\\DS-DIGI.TTF"))
	{
		cout << "Font could not be found" << endl;
	}

	m_BestTime = 10000; // Default best time

	// Initialises timer text
	m_TimerText.setFont(DigiFont);
	m_TimerText.setCharacterSize(35);
	m_TimerText.setPosition(35, 50);
	m_TimerText.setColor(Color::Red);

	// Initialises best time text
	m_BestTimeText.setFont(DigiFont);
	m_BestTimeText.setCharacterSize(35);
	m_BestTimeText.setPosition(35, 90);
	m_BestTimeText.setColor(Color::Red);
	m_BestTimeText.setString("Best Time: 0.0000000");

	// Initialises start line float rect
	m_StartLine.width = 500;
	m_StartLine.height = 500;
	m_StartLine.left = 2100 - (m_StartLine.width / 2);
	m_StartLine.top = 130 - (m_StartLine.height / 2);

	// Initialises mid line float rect
	m_MidLine.width = 500;
	m_MidLine.height = 500;
	m_MidLine.left = 2100;
	m_MidLine.top = 2300;
}

void HUD::updateNeedle(int rpm)
{
	//Creates accurate representation on RPM counter
	float angle = 65;
	angle = angle + (float)rpm * 0.04;
	m_needle.setRotation(angle);
}

void HUD::draw(RenderTarget& target, RenderStates states) const // Draws all UI
{
	target.draw(m_RPMSprite);
	target.draw(m_needle);
	target.draw(m_GearText);
	target.draw(m_TimerText);
	target.draw(m_BestTimeText);
}

void HUD::updateGear(int gear)
{
	m_GearText.setFont(DigiFont);
	if (gear >= 1)
	{
		m_GearText.setString(to_string(gear)); // Keeps gear string equal to the gear
	}
	else if (gear == 0)
	{
		m_GearText.setString("N"); // Uses letter N for neutral instead of gear 0
	}
	else if (gear == -1)
	{
		m_GearText.setString("R"); // Uses gear R for reverse instead of gear -1
	}
	m_GearText.setCharacterSize(70);
	m_GearText.setPosition(845, 715);
	m_GearText.setColor(Color::Red);

}

void HUD::setRPMTexture(vector<Texture>::iterator GivenTexture) // Assigns texture to RPM sprite from texture loader
{
	m_RPMSprite.setTexture(*GivenTexture);
}

Vector2f HUD::getRPMCounterPos() // Returns RPM counter position
{
	return Vector2f(m_RPMSprite.getPosition().x, m_RPMSprite.getPosition().y);
}

void HUD::updateTimers() // Updates timer
{
	m_TimerText.setString(to_string(m_timer.getElapsedTime().asSeconds()));
}

void HUD::resetTimer() // Resets the timer
{
	m_timer.restart();
}

void HUD::updateBestTime() // If current best time is beaten the best time is updated.
{
	if (m_timer.getElapsedTime().asSeconds() < m_BestTime)
	{
		m_BestTime = m_timer.getElapsedTime().asSeconds();
		m_BestTimeText.setString("Best Time: " + to_string(m_BestTime));
	}
}