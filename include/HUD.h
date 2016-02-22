////////////////////////////////////////////////////////////
//
// Car Game - Created by Egor Kharlamov
// Created for C++ Year 2 Coursework at DMU - Games Programming Course
//
// This project is a racing game which contains realistic car physics and polymorphic impulse resolution 
//
////////////////////////////////////////////////////////////
#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Vector.h>

using namespace std;
using namespace sf;

class HUD : public Drawable
{
private:
	RectangleShape m_needle;
	Sprite RPMSprite;
	Font DigiFont;
	Text GearText;
	Text TimerText;
	float BestTime;
	Clock m_timer;
	Text BestTimeText;
public:
	HUD();
	FloatRect StartLine;
	FloatRect MidLine;
	void draw(RenderTarget& target, RenderStates states) const;
	void updateNeedle(int rpm);
	void updateGear(int gear);
	Vector2f getRPMCounterPos();
	void SetRPMTexture(vector<Texture>::iterator GivenTexture);
	void updateTimers();
	void ResetTimer();
	void UpdateBestTime();
	void setupCheckpoints();
};

#endif