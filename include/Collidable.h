#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <SFML/Graphics.hpp>
#include <Vector.h>

using namespace sf;

class Collidable : public Drawable
{
protected:
	
	myVector m_acceleration;
	float m_finvMass;
	myVector getFriction();
public:
	Collidable();
	Collidable(myVector position, myVector acceleration, float invMass, myVector velocity);
	myVector m_position;
	myVector m_velocity;

	virtual void Collide(Collidable* Object2){};
};


#endif