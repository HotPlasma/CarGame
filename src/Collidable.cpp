#include <Collidable.h>

Collidable::Collidable()
{

}

Collidable::Collidable(myVector position, myVector acceleration, float invMass, myVector velocity)
{

}

myVector Collidable::getFriction()
{
	// Velocity multiplied by reasononable coefficent of rubber against concreate mutiplied by earths gravity
	float A = m_velocity.x() * 0.8 * 9.8;
	float B = m_velocity.y() * 0.8 * 9.8;

	myVector frictionForce(A, B);

	return frictionForce; // Returns a reasonable friction vector
}