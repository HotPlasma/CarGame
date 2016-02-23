////////////////////////////////////////////////////////////
//
// Car Game - Created by Egor Kharlamov
// Created for C++ Year 2 Coursework at DMU - Games Programming Course
//
// This project is a racing game which contains realistic car physics and polymorphic impulse resolution 
//
////////////////////////////////////////////////////////////
#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <SFML/Graphics.hpp>
#include <Vector.h>

using namespace sf;

class Collidable : public Drawable
{
protected:
	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	myVector m_acceleration;///< myVector holding the acceleration of a collidable
	float m_finvMass;///< Float holding the inverse mass of a collidable
	////////////////////////////////////////////////////////////
	/// \brief Return a friction by multiplying a velocity by a coefficient and by gravity
	///
	/// \return A myVector of Friction 
	///
	////////////////////////////////////////////////////////////
	myVector getFriction();
public:
	myVector m_position;///< Holds the position of a collidable 
	myVector m_velocity;///< Holds the velocity of a collidable
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Creates a Collidable. Can not be used as Collidable is an abstract class
	///
	////////////////////////////////////////////////////////////
	Collidable(); 
	////////////////////////////////////////////////////////////
	/// \brief Overloaded constructer which contructs the collidable from its position, acceleration, inverse mass and starting velocity 
	///
	/// \param position Position myVector
	/// \param acceleration Acceleration myVector
	/// \param invMass Inverse Mass float
	/// \param velocity Velocity myVector
	///
	////////////////////////////////////////////////////////////
	Collidable(myVector position, myVector acceleration, float invMass, myVector velocity);
	////////////////////////////////////////////////////////////
	/// \brief Polymorphic function collide which allows a collidable to collide with another collidable
	///
	/// Due to its polymorphic nature the function is instantiated in both Tyre 
	/// and Car and allows cars to collide with m_Tyres and m_Tyres to collide with m_Tyres.
	///
	/// \param Object2 A second collidable that the collidable will collide with
	///
	////////////////////////////////////////////////////////////
	virtual void Collide(Collidable* Object2){};
};


#endif

////////////////////////////////////////////////////////////
/// \class Collidable
///
/// Collidable is an abstract class which all objects which can
/// be collided with inherit from. It used late binding to run its Collide 
/// function with any other collideable object.
/// 
/// The advantage of this is that in the future, if any other collidable objects
/// are created they would be very easy to collide with all the other collidables
/// using this system.
/// 
/// This class also serves to retreive friction which I used for a more realistic driving 
/// experience in this game.
////////////////////////////////////////////////////////////