////////////////////////////////////////////////////////////
//
// Car Game - Created by Egor Kharlamov
// Created for C++ Year 2 Coursework at DMU - Games Programming Course
//
// This project is a racing game which contains realistic car physics and polymorphic impulse resolution 
//
////////////////////////////////////////////////////////////
#ifndef TYRE_H
#define TYRE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Collidable.h>

using namespace std;

class Tyre : public Collidable
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Creates a Tyre.
	///
	////////////////////////////////////////////////////////////
	Tyre();

	////////////////////////////////////////////////////////////
	/// \brief Overloaded constructer which contructs the tyre from its position and inverse mass
	///
	/// \param position Position myVector
	/// \param invMass A inverse Mass float
	///
	////////////////////////////////////////////////////////////
	Tyre(myVector position, float invMass);

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	Sprite m_Tyresprite;///< Sprite which represents the car

	float Radius;///< Float which represents the radius of the tyre. Used for collisions.

	////////////////////////////////////////////////////////////
	/// \brief Updates the variables that need to be updated every frame. Used for collision resolution
	///
	/// \param timestep Float game time
	///
	////////////////////////////////////////////////////////////
	void update(float timestep);

	////////////////////////////////////////////////////////////
	/// \brief Allows m_Tyres
	///
	/// \param target Drawable to be drawn
	/// \param states States to be drawn
	///
	////////////////////////////////////////////////////////////
	void draw(RenderTarget & target, RenderStates states) const;

	////////////////////////////////////////////////////////////
	/// \brief Sets the texture to the tyre sprite from the texture loader
	///
	/// Iterator is dereferenced to get texture
	/// \param GivenTexture A iterator of textures in a vector
	///
	////////////////////////////////////////////////////////////
	void setTyreTexture(vector<Texture>::iterator GivenTexture);

	////////////////////////////////////////////////////////////
	/// \brief Polymorphic function derived from collidable class which takes any collidable and allows it to collide with any other collidable in this case a tyre and a tyre. 
	///
	/// \param B A tyre collidable to be collided with
	///
	////////////////////////////////////////////////////////////
	void Collide(Tyre* B);
};

#endif

////////////////////////////////////////////////////////////
/// \class Tyre
///
/// Tyre  is class which holds all infomation about the m_Tyres in the game.
/// To be instantiated it needs to be given a position and inverse mass.
///
/// Tyre is also a collidable, which means that it can collide with any other collidable. It is able to collide with other m_Tyres using the
/// circle-circle collison method. 
///
/// Usage example:
/// \code
/// Tyre(myVector(50,40), 0.3))
/// \endcode
///
///
////////////////////////////////////////////////////////////