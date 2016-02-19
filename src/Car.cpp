#include <Car.h>

using namespace std;

const float g_kfPi = 3.14159;
const float g_kfDegToRad = g_kfPi / 180.0f;


Car::Car(myVector position, myVector acceleration, float invMass, myVector velocity)
{
	//Sets cars varliables from given parameters
	m_position = position;
	m_acceleration = acceleration;
	m_finvMass = invMass;
	m_velocity = velocity;
	m_fRotationAngle = 0;
	m_iGear = 0;
	m_iRPM = 1800;
	m_fSteeringAngle = 0;

	// Sets visual properties of Car
	m_render.setOrigin(Vector2f(25, 15));
	m_render.setPosition(Vector2f(m_position.x(), m_position.y()));
	m_render.scale(1, 1);

	
	//Sets rates of acceleration for each gear
	m_aiAccelRates[0] = 2500;
	m_aiAccelRates[1] = 2200;
	m_aiAccelRates[2] = 1800;
	m_aiAccelRates[3] = 1000;
	m_aiAccelRates[4] = 700;

	//m_aiGearRates[0] = 0.4;
	m_aiGearRates[1] = 0.5f;
	m_aiGearRates[2] = 0.6f;
	m_aiGearRates[3] = 0.7f;
	m_aiGearRates[4] = 0.8f;
	m_aiGearRates[5] = 1.f;

	//Wheels set up
	for (int i = 0; i < 2; i++)
	{
		FrontWheel[i].setSize(Vector2f(10, 4));
		RearWheel[i].setSize(Vector2f(10, 4));
		FrontWheel[i].setOrigin(FrontWheel[i].getSize() / 2.f);
		RearWheel[i].setOrigin(RearWheel[i].getSize() / 2.f);
		FrontWheel[i].setFillColor(Color::Black);
		RearWheel[i].setFillColor(Color::Black);
	}
	

}

Car::Car()
{

}


void Car::draw(RenderTarget & target, RenderStates states) const
{
	for (int i = 0; i < 2; i++)
	{
		target.draw(FrontWheel[i]);
		target.draw(RearWheel[i]);
	}
	
	target.draw(m_render);
}

void Car::Accelerate() //Accelerates car by RPM multiplied by the rotation of the car after being affected by friction
{
	m_acceleration = RotationVector.multiply(m_iRPM * m_aiGearRates[m_iGear]).subtract(getFriction());
	//cout << getFriction().x() << "   " << getFriction().y() << endl;
	//cout << m_aiGearRates[m_iGear] << endl;
	//cout << m_velocity.x() << "     " << m_velocity.y() << endl;
}

void Car::Neutral()
{
	m_acceleration = RotationVector.multiply(m_iRPM - 1800).subtract(getFriction());
}

void Car::ReversingAccel()
{
	m_iRPM = 1800;
	m_acceleration = RotationVector.multiply(-500).subtract(getFriction());
	
}

void Car::Turn() //Turns vehicle left or right depending on key pressed
{

	if (RotatingRight)
	{
		m_fSteeringAngle += 0.5;
	}

	else if (RotatingLeft)
	{
		m_fSteeringAngle -= 0.5;
	}
}

void Car::GearsManagement(float timestep)
{
	//Gears change RPM based on acceleration rates in m_aiAccelRates array

	if (m_iGear > 0) // If not neutral
	{
		if (m_iGear < 5) // ...and not in highest gear
		{
			// Simple Euler integration of RPM value
			m_iRPM += timestep * m_aiAccelRates[m_iGear - 1];
			// Check if should change up
			if (m_iRPM > 6500)
			{
				m_iGear++;
				m_iRPM = 3500;
			}
		}
		else if (m_iRPM < 8500)
		{
			// Simple Euler integration of RPM value
			m_iRPM += timestep * m_aiAccelRates[m_iGear - 1];
		}
	}

	else

	{
		if (m_iGear > 1)
		{
			// Simple Euler integration of RPM value
			m_iRPM -= timestep * m_aiAccelRates[3];
			// Check if we should change down
			if (m_iRPM < 2500)
			{
				m_iGear--;
				m_iRPM = 3750;
			}
		}
		else
		{
			if (m_iRPM > 1800)
			{
				// Simple Euler integration of RPM value
				m_iRPM -= timestep * m_aiAccelRates[3];
			}
		}
	}
}

void Car::update(float timestep)
{

	// Limits steering angle to realistic level
	if (m_fSteeringAngle > 30)
	{
		m_fSteeringAngle = 30;
	}
	if (m_fSteeringAngle < -30)
	{
		m_fSteeringAngle = -30;
	}

	//cout << m_fSteeringAngle;
	//cout << m_velocity.x() << "     " << m_velocity.y() << endl;

	// Creates vector facing same direction as car
	RotationVector = myVector(cosf(g_kfDegToRad * m_fRotationAngle), sinf(g_kfDegToRad * m_fRotationAngle));
	myVector SteeringVector(cosf((m_fRotationAngle + m_fSteeringAngle) * g_kfDegToRad), sinf((m_fRotationAngle + m_fSteeringAngle) * g_kfDegToRad));
	m_render.setRotation(m_fRotationAngle); // Sets rotation 

	float fDisplacement = m_velocity.magnitude() * timestep;
	float fWheelBase = m_render.getLocalBounds().width * 0.65f;

	if (m_velocity.dotProduct(SteeringVector) < 0)
	{
		fDisplacement = -fDisplacement;
	}

	myVector fWheelPos[2];
	myVector rWheelPos[2];

	myVector PerpCarAngle(-RotationVector.y(), RotationVector.x());

	fWheelPos[0].set(m_position.add(RotationVector.multiply(fWheelBase / 2)));
	fWheelPos[1].set(m_position.add(RotationVector.multiply(fWheelBase / 2)));
	//fWheelPos[1].set(m_position.add(RotationVector.multiply(fWheelBase / 2)));
	rWheelPos[0].set(m_position.subtract(RotationVector.multiply(fWheelBase / 2)));

	fWheelPos[0] = fWheelPos[0].add(SteeringVector.multiply(fDisplacement));
	rWheelPos[0] = rWheelPos[0].add(RotationVector.multiply(fDisplacement));

	for  (int i = 0; i < 2; i++)
	{
		/*FrontWheel[0].setPosition(Vector2f(fWheelPos[0].x(), fWheelPos[0].y()));
		RearWheel[0].setPosition(Vector2f(rWheelPos[0].x(), rWheelPos[0].y()));*/

		FrontWheel[i].setRotation(m_fSteeringAngle + m_fRotationAngle);
		RearWheel[i].setRotation(m_fRotationAngle);
	}

	// Sets up my vectors for my wheels
	FrontWheel[0].setPosition(Vector2f(fWheelPos[0].add(PerpCarAngle.multiply(10)).Convert2f()));
	FrontWheel[1].setPosition(Vector2f(fWheelPos[0].add(PerpCarAngle.multiply(-12)).Convert2f()));
	RearWheel[0].setPosition(Vector2f(rWheelPos[0].add(PerpCarAngle.multiply(-12)).Convert2f()));
	RearWheel[1].setPosition(Vector2f(rWheelPos[0].add(PerpCarAngle.multiply(11)).Convert2f()));

	if (m_iGear >= 1)
	{
		Accelerate();
	}

	// Detects if user is trying to turn
	if (RotatingLeft || RotatingRight)
	{
		Turn();
	}
	else
	{
		if (m_fSteeringAngle > 0)
		m_fSteeringAngle -= 1;
		else if (m_fSteeringAngle < 0)
		{
			m_fSteeringAngle += 1;
		}
	}
	
	if (m_iGear == 0)
	{
		Neutral();
	}

	if (m_iGear == -1)
	{
		ReversingAccel();
	}

	GearsManagement(timestep); // Changes gears and RPM
	
	m_velocity = m_velocity.add(m_acceleration.multiply(timestep));
	m_position.setX((fWheelPos[0].x() + rWheelPos[0].x()) / 2);
	m_position.setY((fWheelPos[0].y() + rWheelPos[0].y()) / 2);
	m_fRotationAngle = atan2f(fWheelPos[0].y() - rWheelPos[0].y(), fWheelPos[0].x() - rWheelPos[0].x()) / g_kfDegToRad;
	m_render.setPosition(Vector2f(m_position.x(), m_position.y()));
}

Vector2f Car::ReturnCarPos()
{
	return Vector2f(m_render.getPosition());
}
//
void Car::Collide(Tyre* B)
{
	//Creates a position for a tyre minus the position of car
	myVector LocalTyrePos(B->TyreSprite.getPosition().x - m_render.getPosition().x, B->TyreSprite.getPosition().y - m_render.getPosition().y);
	
	//Will hold closest point within car pointing towards tyre 
	myVector Clamp;
		
	//Half Extents are set as half the size of the car
	myVector HalfExtents(m_render.getLocalBounds().width / 2, m_render.getLocalBounds().height / 2);

	//Rotates tyre around by the rotation of the car
	LocalTyrePos.set(myVector::RotateVector(LocalTyrePos, -m_render.getRotation()));

	//Sets up Clamp of car against the LocalTyrePos
	if (LocalTyrePos.x() >= 0)
	{
		Clamp.setX(fmin(LocalTyrePos.x(), HalfExtents.x()));
	}
	if (LocalTyrePos.x() < 0)
	{
		Clamp.setX(fmax(LocalTyrePos.x(), -HalfExtents.x()));
	}
	if (LocalTyrePos.y() >= 0)
	{
		Clamp.setY(fmin(LocalTyrePos.y(), HalfExtents.y()));
	}
	if (LocalTyrePos.y() < 0)
	{
		Clamp.setY(fmax(LocalTyrePos.y(), -HalfExtents.y()));
	}
	
	//Difference = Rotated tyre position - Clamp
	myVector Diff(LocalTyrePos.subtract(Clamp));
	
	//Final distance is the maginitude of the difference minus the radius of the tyre
	float Distance = Diff.magnitude() - B->Radius;

	//std::cout << Distance << endl;

	if (Distance <= -0.2) //If collided
	{
		myVector CollisonNorm(Distance, 0); //Create a collision normal vector and insert distance
		CollisonNorm = myVector::RotateVector(CollisonNorm, m_render.getRotation()); //Rotate collision normal by the roatation of the car
		myVector NewVel;
		//New Velocity is equal to -(1+e)*Collision Normal*(Collision Normal.Velocity)
		NewVel.set(CollisonNorm.multiply(-(1 + 0.2)).multiply(CollisonNorm.dotProduct(m_velocity)));

		if (NewVel.x() >= 0)
		{
			NewVel.setX(fmin(NewVel.x(), 2000));
		}
		if (NewVel.x() < 0)
		{
			NewVel.setX(fmax(NewVel.x(), -2000));
		}
		if (NewVel.y() >= 0)
		{
			NewVel.setY(fmin(NewVel.y(), 2000));
		}
		if (NewVel.y() < 0)
		{
			NewVel.setY(fmax(NewVel.y(), -2000));
		}


		//std::cout << NewVel.x() << "   " << NewVel.y() << endl;
		m_iRPM = 1800;
		// Changes velocity to resolve collision
		m_velocity = m_velocity.add(NewVel);

		B->m_velocity = B->m_velocity.add(NewVel.MakeNegetive());


		//myVector CollisionNormal = myVector::normalise(Clamp);

		//float J;
		//J = (-(1 + 0.3) * (m_velocity.subtract(B->m_velocity)).dotProduct(CollisionNormal)) / (m_finvMass + B->m_finvMass);

		//m_velocity = m_velocity.add(CollisionNormal.multiply(J).multiply(m_finvMass));    // m_velocity + (myVector::normalise(Distance).multiply(J) / m_finvMass;
		//B->m_velocity = B->m_velocity.add(CollisionNormal.multiply(-J).multiply(B->m_finvMass));


		//m_position = m_position.add(CollisionNormal.multiply(CollisionNormal.multiply(Distance)));
	}

}

void Car::CarSetPos(myVector Pos)
{
	m_render.setPosition(Vector2f(Pos.x(), Pos.y()));
}

void Car::setCarTexture(vector<Texture>::iterator GivenTexture)
{
	CarTex = *GivenTexture;
	m_render.setTexture(CarTex);
}