#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vector.h"

using namespace std;
using namespace sf;

class Speedometer : public Drawable
{
private:
	VertexArray m_spedo;
	RectangleShape m_needle;
	Sprite RPMSprite;
	Texture RPMTexture;
public:
	Speedometer();
	void draw(RenderTarget& target, RenderStates states) const;
	void updateNeedle(int rpm);
};

#endif