#ifndef TYRE_H
#define TYRE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Collidable.h>

using namespace std;

class Tyre : public Collidable
{
public:

	Tyre();
	Tyre(myVector position, float invMass);
	//CircleShape TyreShape;
	Sprite TyreSprite;
	float Radius;
	void update(float timestep);
	void draw(RenderTarget & target, RenderStates states) const;
	void setTyreTexture(vector<Texture>::iterator GivenTexture);

	void Collide(Tyre* B);

	Sprite getTyreSprite();

};

#endif