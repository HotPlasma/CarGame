#include <Vector.h>


myVector::myVector()
{
	m_adVector[0] = 0;
	m_adVector[1] = 0;
}

myVector::myVector(double A, double B)
{
	m_adVector[0] = A;
	m_adVector[1] = B;
}

myVector myVector::set(const double A,const double B) const
{
	return myVector(A, B);
}

myVector myVector::add(const myVector other) const
{
	double i;
	double j;

	i = other.m_adVector[0] + m_adVector[0];
	j = other.m_adVector[1] + m_adVector[1];

	return myVector(i, j);
}

myVector myVector::subtract(const myVector other) const
{
	double i;
	double j;


	i = m_adVector[0] - other.m_adVector[0];
	j = m_adVector[1] - other.m_adVector[1];

	return myVector(i, j);
}

myVector myVector::multiply(const myVector other) const
{
	double i;
	double j;

	i = other.m_adVector[0] * m_adVector[0];
	j = other.m_adVector[1] * m_adVector[1];

	return myVector(i, j);
}



myVector myVector::multiply(const float scalar) const
{
	double i;
	double j;

	i = scalar * m_adVector[0];
	j = scalar * m_adVector[1];

	return myVector(i, j);
}

double myVector::dotProduct(const myVector other) const
{
	double i;
	double j;

	i = m_adVector[0] * other.m_adVector[0];
	j = m_adVector[1] * other.m_adVector[1];

	return i + j;

	
}

myVector myVector::crossProduct(const myVector other) const
{
	// ALMOST DEFINITELY WRONG
	double i;
	double j;

	i = m_adVector[0] * other.m_adVector[1];
	j = other.m_adVector[0] * m_adVector[0];

	return myVector(i, j);

	//empVect.set(x()  Vect2.y(), Vect2.x()  x());
}

float myVector::magnitude() const
{
	double i;
	double j;

	i = m_adVector[0] * m_adVector[0];
	j = m_adVector[1] * m_adVector[1];

	return sqrtf(i + j);
	
}

void myVector::set(myVector Setter)
{
	m_adVector[0] = Setter.m_adVector[0];
	m_adVector[1] = Setter.m_adVector[1];
} 

void myVector::setX(const double A)
{
	m_adVector[0] = A;
}

void myVector::setY(const double B)
{
	m_adVector[1] = B;
}

double myVector::x()
{
	return m_adVector[0];
}
double myVector::y()
{
	return m_adVector[1];
}

myVector myVector::RotateVector(myVector Vector, float Angle)
{
	Angle = Angle * (3.1415 / 180);

	myVector rotatedVect;
	rotatedVect.setX((Vector.x() * cosf(Angle)) + (Vector.y() * -sinf(Angle)));
	rotatedVect.setY((Vector.x() * sinf(Angle)) + (Vector.y() * cosf(Angle)));

	return rotatedVect;
}

myVector myVector::normalise(myVector vector)
{
	return vector.multiply(1.0f / vector.magnitude());
}

Vector2f myVector::Convert2f() // Converts one of my vectors into a Vector2f. Necessary for specific functions in sfml
{
	Vector2f ConvertedVector(m_adVector[0], m_adVector[1]);

	return ConvertedVector;
}

myVector myVector::ConvertToMyVector(Vector2f vector)
{
	return myVector(vector.x, vector.y);
}

myVector myVector::MakeNegetive()
{
	m_adVector[0] = -m_adVector[0];
	m_adVector[1] = -m_adVector[1];

	return myVector(m_adVector[0], m_adVector[1]);
}
