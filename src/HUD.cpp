#include <HUD.h>
#include <Car.h>

HUD::HUD()
{

	//Rectangle to contain sprite
	//RectangleShape RPMRect;

	RPMSprite.setPosition(1000 - 279, 800 - 282); // Sets RPM counter to bottom left corner

	//RPMSprite.setTexture(RPMTexture);
	RPMSprite.setOrigin(RPMSprite.getLocalBounds().width / 2, RPMSprite.getLocalBounds().height / 2); // Sets origin to the centre
	RPMSprite.setScale(1, 1);
	//Set position of sprite within rectangle
	//RPMSprite.setPosition(RPMSprite.getPosition().x + RPMSprite.getLocalBounds().width / 2, RPMSprite.getPosition().y + RPMSprite.getLocalBounds().height / 2);


	//Create needle and set position within centre of RPM counter
	m_needle.setFillColor(Color::Green);
	m_needle.setSize(Vector2f(80, 10));
	m_needle.setPosition(1000-140, 800-140);
	m_needle.setOrigin(Vector2f(m_needle.getSize().x / 2 - 40, m_needle.getSize().y / 2));

	if (!DigiFont.loadFromFile("..\\assets\\HUD\\DS-DIGI.TTF"))
	{
		cout << "Font could not be found" << endl;
	}

	BestTime = 10000;

	TimerText.setFont(DigiFont);
	TimerText.setCharacterSize(35);
	TimerText.setPosition(100, 100);
	TimerText.setColor(Color::Red);

	BestTimeText.setFont(DigiFont);
	BestTimeText.setCharacterSize(35);
	BestTimeText.setPosition(100, 140);
	BestTimeText.setColor(Color::Red);
	BestTimeText.setString("Best Time: 0.0000000");
}

void HUD::updateNeedle(int rpm)
{
	//Creates fairly accurate representation on RPM counter
	float angle = 65;
	angle = angle + (float)rpm * 0.04;
	m_needle.setRotation(angle);
}

void HUD::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(RPMSprite);
	target.draw(m_needle);
	target.draw(GearText);
	target.draw(TimerText);
	target.draw(BestTimeText);
}

void HUD::updateGear(int gear)
{
	GearText.setFont(DigiFont);
	if (gear >= 1)
	{
		GearText.setString(to_string(gear));
	}
	else if (gear == 0)
	{
		GearText.setString("N");
	}
	else if (gear == -1)
	{
		GearText.setString("R");
	}
	GearText.setCharacterSize(70);
	GearText.setPosition(845, 715);
	GearText.setColor(Color::Red);

}

void HUD::SetRPMTexture(vector<Texture>::iterator GivenTexture)
{
	RPMTexture = *GivenTexture;
	RPMSprite.setTexture(RPMTexture);
}
Vector2f HUD::getRPMCounterPos()
{
	return Vector2f(RPMSprite.getPosition().x, RPMSprite.getPosition().y);
}

void HUD::updateTimers()
{
	TimerText.setString(to_string(m_timer.getElapsedTime().asSeconds()));
}

void HUD::ResetTimer()
{
	m_timer.restart();
}

void HUD::UpdateBestTime()
{
	if (m_timer.getElapsedTime().asSeconds() < BestTime)
	{
		BestTime = m_timer.getElapsedTime().asSeconds();
		BestTimeText.setString("Best Time: " + to_string(BestTime));
	}
}

void HUD::setupCheckpoints()
{
	StartLine.width = 500;
	StartLine.height = 500;
	StartLine.left = 2100 - (StartLine.width / 2);
	StartLine.top = 130 - (StartLine.height / 2);
	
	MidLine.width = 500;
	MidLine.height = 500;
	MidLine.left = 2100;
	MidLine.top = 2400;

	//StartLine.setPosition(Vector2f(2100, 130));
	//StartLine.setSize(Vector2f(500, 500));
	//StartLine.setOrigin(StartLine.getSize().x / 2.0f, StartLine.getSize().y / 2.0f); // Sets origin to centre
	//StartLine.setFillColor(Color::White); // Green
	//StartLine.setOutlineThickness(1);
	//StartLine.setOutlineColor((Color(0, 0, 0)));

	//MidLine.setPosition(Vector2f(2100, 2400));
	//MidLine.setSize(Vector2f(500, 500));
	//MidLine.setOrigin(StartLine.getSize().x / 2.0f, StartLine.getSize().y / 2.0f); // Sets origin to centre
	//MidLine.setFillColor(Color::White); // Green
	//MidLine.setOutlineThickness(1);
	//MidLine.setOutlineColor((Color(0, 0, 0)));
}