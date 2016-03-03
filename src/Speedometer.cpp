#include "Speedometer.h"

Speedometer::Speedometer()
{
	if (!RPMTexture.loadFromFile("..\\assets\\HUD\\RPM.png"))
	{
		cout << "Could not load RPM.png" << endl;
	}

	RectangleShape RPMRect;

	RPMRect.setSize(Vector2f(697, 705));
	RPMRect.setPosition(1000 - 279, 800 - 282);

	RPMSprite.setTexture(RPMTexture);
	RPMSprite.setOrigin(RPMRect.getSize().x / 2, RPMRect.getSize().x / 2);
	RPMSprite.setScale(1, 1);
	RPMSprite.setPosition(RPMRect.getPosition().x + RPMRect.getSize().x / 2, RPMRect.getPosition().y + RPMRect.getSize().y / 2);

	m_needle.setFillColor(Color::Green);
	m_needle.setSize(Vector2f(80, 10));
	m_needle.setPosition(1000-140, 800-140);
	m_needle.setOrigin(Vector2f(m_needle.getSize().x / 2 - 40, m_needle.getSize().y / 2));
	m_needle.setRotation(-45);
	
}

void Speedometer::updateNeedle(int rpm)
{
	float angle = (float)rpm * 0.027143 - 93.85; // Basic linear equation with some magic numbers - not ideal foe reues, could you do better?
	m_needle.setRotation(angle);
}

void Speedometer::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(RPMSprite);
	//target.draw(m_spedo);
	target.draw(m_needle);
}