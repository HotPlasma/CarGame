#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class myVector
{
private:
	double m_adVector[2];

public:
	myVector();
	myVector(double A, double B);
	void set(myVector Setter);
	myVector set(const double A,const double B) const;
	void setX(const double A);
	void setY(const double B);
	myVector add(const myVector other) const; 
	myVector subtract(const myVector other) const;
	myVector multiply(const myVector other) const;
	myVector multiply(const float scalar) const;
	float magnitude() const;
	double dotProduct(const myVector other) const;
	myVector crossProduct(const myVector other) const;
	static myVector RotateVector(myVector Vector, float Angle);
	static myVector normalise(myVector vector);
	double x();
	double y();
	Vector2f Convert2f();
	static myVector ConvertToMyVector(Vector2f vector);
	myVector MakeNegetive();
};


#endif