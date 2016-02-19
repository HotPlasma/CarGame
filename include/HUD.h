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
	Texture RPMTexture;
	Font DigiFont;
	Text GearText;
public:
	HUD();
	void draw(RenderTarget& target, RenderStates states) const;
	void updateNeedle(int rpm);
	void updateGear(int gear);
	Vector2f getRPMCounterPos();
	void SetRPMTexture(vector<Texture>::iterator GivenTexture);
};

#endif