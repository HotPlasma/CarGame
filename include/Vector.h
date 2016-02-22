////////////////////////////////////////////////////////////
//
// Car Game - Created by Egor Kharlamov
// Created for C++ Year 2 Coursework at DMU - Games Programming Course
//
// This project is a racing game which contains realistic car physics and polymorphic impulse resolution 
//
////////////////////////////////////////////////////////////
#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class myVector
{
private:
	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	double m_adVector[2];///< A 2 dimensional array of doubles which holds the values for the MyVectors

public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Creates a myVector. Default values are (0,0) 
	///
	////////////////////////////////////////////////////////////
	myVector(); 

	////////////////////////////////////////////////////////////
	/// \brief Construct the myVector from its coordinates
	///
	/// \param A X coordinate
	/// \param B Y coordinate
	///
	////////////////////////////////////////////////////////////
	myVector(double A, double B);

	////////////////////////////////////////////////////////////
	/// \brief Set a vector to be another myVector
	///
	/// \param Setter The myVector which the current vector will be set to.
	///
	////////////////////////////////////////////////////////////
	void set(myVector Setter);
	myVector set(const double A,const double B) const;

	////////////////////////////////////////////////////////////
	/// \brief Set only the X coordinate from the myVector
	///
	/// \param A X coordinate
	/// 
	///
	////////////////////////////////////////////////////////////
	void setX(const double A);
	////////////////////////////////////////////////////////////
	/// \brief Set only the Y coordinate from the myVector
	///
	/// \param B Y coordinate
	/// 
	///
	////////////////////////////////////////////////////////////
	void setY(const double B);

	////////////////////////////////////////////////////////////
	/// \brief Adds to myVectors together
	///
	/// \param other Vector to be added
	///
	/// \return Result from addition
	///
	/// Usage example:
	/// \code
	/// myVectorA.add(myVectorB);
	///	\endcode
	////////////////////////////////////////////////////////////
	myVector add(const myVector other) const; 

	////////////////////////////////////////////////////////////
	/// \brief Subtract given myVector from another myVector
	///
	/// \param other myVector to be subtracted
	///
	///
	/// \return Result from subtraction
	/// Usage example:
	/// \code
	/// myVectorA.subtract(myVectorB);
	///	\endcode
	////////////////////////////////////////////////////////////
	myVector subtract(const myVector other) const;

	////////////////////////////////////////////////////////////
	/// \brief Multiplies given Vector by other Vector
	///
	/// \param other myVector to multiply by
	///
	/// \return Result from multiplication
	/// 
	/// Usage example:
	/// \code
	/// myVectorA.multiply(myVectorB);
	///	\endcode
	////////////////////////////////////////////////////////////
	myVector multiply(const myVector other) const;

	////////////////////////////////////////////////////////////
	/// \brief Multiplies given Vector by a scalar
	///
	/// \param scalar A float to multiply the myVector by
	///
	/// \return Result from multiplication
	///
	/// Usage example:
	/// \code
	/// myVectorA.multiply(7.0f);
	///	\endcode
	////////////////////////////////////////////////////////////
	myVector multiply(const float scalar) const;

	////////////////////////////////////////////////////////////
	/// \brief Gets the magnitude of a myVector
	///
	/// \return Magnitude of the given myVector
	///
	/// Usage example:
	/// \code
	/// myVectorMag = myVectorA.magnitude();
	///	\endcode
	////////////////////////////////////////////////////////////
	float magnitude() const;

	////////////////////////////////////////////////////////////
	/// \brief Calculates the dot product of two myVectors
	///
	/// \return The dot product of the two myVectors
	///
	/// \param other 
	/// Usage example:
	/// \code
	/// myVectorA.dotProduct(myVectorB);
	///	\endcode
	////////////////////////////////////////////////////////////
	double dotProduct(const myVector other) const;

	////////////////////////////////////////////////////////////
	/// \brief Calculates the cross product of two myVectors
	///
	/// \return The cross product of the two myVectors
	///
	/// Usage example:
	/// \code
	/// myVectorA.crossProduct(myVectorB);
	///	\endcode
	////////////////////////////////////////////////////////////
	myVector crossProduct(const myVector other) const;

	////////////////////////////////////////////////////////////
	/// \brief Rotates a given MyVector by an angle
	///
	/// \return Rotated myVector
	///
	/// Usage example:
	/// \code
	/// myVectorA = myVectorA.RotateVector(55);
	///	\endcode
	////////////////////////////////////////////////////////////
	myVector RotateVector(float Angle);

	////////////////////////////////////////////////////////////
	/// \brief Static function which normalises a given myVector
	///
	/// \return Normalised Vector
	///
	/// Usage example:
	/// \code
	/// VectorANorm = myVector::normalise(myVectorA);
	///	\endcode
	////////////////////////////////////////////////////////////
	static myVector normalise(myVector vector);

	////////////////////////////////////////////////////////////
	/// \brief Static function which normalises a given myVector
	///
	/// \return Normalised Vector
	///
	/// Usage example:
	/// \code
	/// VectorANorm = myVector::normalise(myVectorA);
	///	\endcode
	////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////
	/// \brief A getter for the X coordinate of a myVector
	///
	/// \return X coordinate of a myVector
	///
	/// Usage example:
	/// \code
	/// myVectorA.x();
	///	\endcode
	////////////////////////////////////////////////////////////
	double x();

	////////////////////////////////////////////////////////////
	/// \brief A getter for the Y coordinate of a myVector
	///
	/// \return Y coordinate of a myVector
	///
	/// Usage example:
	/// \code
	/// myVectorA.y();
	///	\endcode
	////////////////////////////////////////////////////////////
	double y();

	////////////////////////////////////////////////////////////
	/// \brief Converts a myVector to a Vector2f
	///
	/// \return Vector2f with the same X,Y values as the given myVector
	///
	/// Usage example:
	/// \code
	/// ConVector2f = myVectorA.Convert2f;
	///	\endcode
	////////////////////////////////////////////////////////////
	Vector2f Convert2f();

	////////////////////////////////////////////////////////////
	/// \brief Static function which converts a vector2f into a myVector
	///
	/// \return myVector with the same X,Y values as the given Vector2f
	///
	/// Usage example:
	/// \code
	/// myVectorA = myVector::ConvertToMyVector(Vector2fA);
	///	\endcode
	////////////////////////////////////////////////////////////
	static myVector ConvertToMyVector(Vector2f vector);

	////////////////////////////////////////////////////////////
	/// \brief Reverses the myVectors polarity 
	///
	/// \return myVector with reversed polarity
	///
	/// Usage example:
	/// \code
	/// NegativemyVectorA = myVectorA.MakeNegative();
	///	\endcode
	////////////////////////////////////////////////////////////
	myVector MakeNegetive();
};


#endif

////////////////////////////////////////////////////////////
/// \class myVector
///
/// A mathematical class that expands on sf::Vector2f by adding the 
/// vector operations they lack such as dot product and rotation. They can
/// also easily be converted to sf::Vector2f or myVectors so they are very 
/// easy to use in conjunction with sfml. 
/// 
/// 
/// 
/// 
/// 
/// 
/// 
///
/// 
/// 
///
/// Usage example:
/// \code
/// myVector MyVectorA(0.5,25);
/// \endcode
///
///
////////////////////////////////////////////////////////////