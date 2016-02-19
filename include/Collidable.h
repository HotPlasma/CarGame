#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <SFML/Graphics.hpp>
#include <Vector.h>

using namespace sf;

class Collidable : public Drawable
{
public:
	Collidable();
	Collidable(myVector position, myVector acceleration, float invMass, myVector velocity);
	myVector m_position;
	myVector m_acceleration;
	float m_finvMass;
	myVector m_velocity;
	myVector getFriction();
	
	//float Clamp(RectangleShape Rectangle, CircleShape Circle);
	//float CircleCircle(CircleShape Circle1, CircleShape Circle2);
	//void draw(RenderTarget &target, RenderStates states) const;

	virtual void Collide(Collidable* Object2){};
};


#endif