#include <Tyre.h>

Tyre::Tyre()
{

}

Tyre::Tyre(myVector position, float invMass)
{
	// Initialises tyre sprite
	m_Tyresprite.setOrigin(40, 40);
	m_Tyresprite.setScale(1, 1);
	m_finvMass = invMass;
	m_acceleration.set(0, 0);
	m_velocity.set(0, 0);
	Radius = 40;
	m_Tyresprite.setPosition(position.x(), position.y());
	Collidable::m_position = position; // Gives tyres position in collidable.
}

void Tyre::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(m_Tyresprite);
}

void Tyre::Collide(Tyre* B) // Collision between two tyres
{
	//Tyre positions
	myVector CircleA(m_Tyresprite.getPosition().x, m_Tyresprite.getPosition().y);
	myVector CircleB(B->m_Tyresprite.getPosition().x, B->m_Tyresprite.getPosition().y);

	//Gets Tyre radii
	float RadiusA = Radius;
	float RadiusB = B->Radius;

	float SumofRadii = RadiusA + RadiusB;

	myVector Distance;
	Distance.set(CircleB.subtract(CircleA)); // Distance is equal to the B minus A

	float DistMag = Distance.magnitude();

	float FinalDist = DistMag - SumofRadii; // Final distance is equal to the magnitude of distance - the sum of both radii

	if (FinalDist <= 0) // Collision has occured
	{

		myVector CollisionNormal = myVector::normalise(Distance);

		// Collision resolution
		float J;
		J = (-(1 + 0.5) * (m_velocity.subtract(B->m_velocity)).dotProduct(CollisionNormal)) / (m_finvMass + B->m_finvMass);

		m_velocity = m_velocity.add(CollisionNormal.multiply(J).multiply(m_finvMass));
		B->m_velocity = B->m_velocity.add(CollisionNormal.multiply(-J).multiply(B->m_finvMass));

		// Position correction
		m_position = m_position.add(CollisionNormal.multiply(FinalDist));
	}
}


void Tyre::setTyreTexture(vector<Texture>::iterator GivenTexture) // Assigns texture to tyres
{
	m_Tyresprite.setTexture(*GivenTexture);
}

void Tyre::update(float timestep)
{

	m_acceleration = myVector(0, 0).subtract(getFriction());

	// Euler for collisions for tyres
	m_velocity = m_velocity.add(m_acceleration.multiply(timestep));
	m_position = m_position.add(m_velocity.multiply(timestep));
	m_Tyresprite.setPosition(Vector2f(m_position.x(), m_position.y()));
	
}