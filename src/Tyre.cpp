#include <Tyre.h>

Tyre::Tyre()
{

}

Tyre::Tyre(myVector position, float invMass)
{
	m_Tyresprite.setOrigin(40, 40);
	m_Tyresprite.setScale(1, 1);
	m_finvMass = invMass;
	m_acceleration.set(0, 0);
	m_velocity.set(0, 0);
	Radius = 40;
	m_Tyresprite.setPosition(position.x(), position.y());
	Collidable::m_position = position;
}

void Tyre::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(m_Tyresprite, states);
}

void Tyre::Collide(Tyre* B)
{
	myVector CircleA(m_Tyresprite.getPosition().x, m_Tyresprite.getPosition().y);
	myVector CircleB(B->m_Tyresprite.getPosition().x, B->m_Tyresprite.getPosition().y);

	float RadiusA = Radius;
	float RadiusB = B->Radius;

	float SumofRadii = RadiusA + RadiusB;

	myVector Distance;
	Distance.set(CircleB.subtract(CircleA));

	float DistMag = Distance.magnitude();

	float FinalDist = DistMag - SumofRadii;

	if (FinalDist <= 0)
	{
		//err() << "colliding" << endl;
		//myVector CollisonNorm(FinalDist, 0); //Create a collision normal vector and insert distance
		//myVector NewVel;
		////New Velocity is equal to -(1+e)*Collision Normal*(Collision Normal.Velocity)
		//NewVel.set(CollisonNorm.multiply(-(1 + 0.2)).multiply(CollisonNorm.dotProduct(m_velocity)));

		//if (NewVel.x() >= 0)
		//{
		//	NewVel.setX(fmin(NewVel.x(), 2000));
		//}
		//if (NewVel.x() < 0)
		//{
		//	NewVel.setX(fmax(NewVel.x(), -2000));
		//}
		//if (NewVel.y() >= 0)
		//{
		//	NewVel.setY(fmin(NewVel.y(), 2000));
		//}
		//if (NewVel.y() < 0)
		//{
		//	NewVel.setY(fmax(NewVel.y(), -2000));
		//}


		////std::cout << NewVel.x() << "   " << NewVel.y() << endl;
		//// Changes velocity to resolve collision
		//m_velocity = m_velocity.add(NewVel);

		//B->m_velocity = B->m_velocity.add(NewVel);

		myVector CollisionNormal = myVector::normalise(Distance);

		float J;
		J = (-(1 + 0.5) * (m_velocity.subtract(B->m_velocity)).dotProduct(CollisionNormal)) / (m_finvMass + B->m_finvMass);

		m_velocity = m_velocity.add(CollisionNormal.multiply(J).multiply(m_finvMass));
		B->m_velocity = B->m_velocity.add(CollisionNormal.multiply(-J).multiply(B->m_finvMass));


		m_position = m_position.add(CollisionNormal.multiply(FinalDist));
	}
}


void Tyre::setTyreTexture(vector<Texture>::iterator GivenTexture)
{
	m_Tyresprite.setTexture(*GivenTexture);
}

void Tyre::update(float timestep)
{
	m_acceleration = myVector(0, 0).subtract(getFriction());

	m_velocity = m_velocity.add(m_acceleration.multiply(timestep));
	m_position = m_position.add(m_velocity.multiply(timestep));
	m_Tyresprite.setPosition(Vector2f(m_position.x(), m_position.y()));
	
}