////////////////////////////////////////////////////////////
//
// Car Game - Created by Egor Kharlamov
// Created for C++ Year 2 Coursework at DMU - Games Programming Course
//
// This project is a racing game which contains realistic car physics and polymorphic impulse resolution 
//
////////////////////////////////////////////////////////////
#ifndef CAR_H
#define CAR_H

#include <Collidable.h>
#include <iostream>
#include <HUD.h>
#include <Tyre.h>

using namespace sf;

class Car : public Collidable
{
public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Creates a Car.
	///
	////////////////////////////////////////////////////////////
	Car();

	////////////////////////////////////////////////////////////
	/// \brief Overloaded constructer which contructs the car from its position, acceleration, inverse mass and starting velocity 
	///
	/// \param position Position myVector
	/// \param acceleration Acceleration myVector
	/// \param invMass Inverse Mass float
	/// \param velocity Velocity myVector
	///
	////////////////////////////////////////////////////////////
	Car(myVector position, myVector acceleration, float invMass, myVector velocity);

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	RectangleShape m_FrontWheel[2]; ///< Array of two rectangle shapes which will be my front wheels 
	RectangleShape m_RearWheel[2]; ///< Array of two rectangle shapes which will be my rear wheels 
	int m_iRPM; ///< Integer which holds the Rotations Per Minute by which the car will accelerate
	int m_iGear; ///< Integer which holds which gear the car is in
	int m_aiAccelRates[5]; ///< Array of integers which store the rates of acceleration for each gear
	float m_afGearRates[6]; ///< Array of floats which hold what value the acceleration rates are multiplied by in order for the car to gain gain speed when accelerating. 

	float m_fSteeringAngle; ///< Float which contains the angle my m_Tyres would face

	float m_fRotationAngle; ///< Float which holds the rotation angle of my car
	myVector m_RotationVector; ///< Vector which contains the direction my car is facing 

	bool m_bRotatingRight = false;///< Rotational bool for right direction
	bool m_bRotatingLeft = false;///< Roational bool for left direction

	Sprite m_render; ///< Sprite which represents the car

	////////////////////////////////////////////////////////////
	/// \brief Accelerates car by RPM of each gear multiplied by the rotation of the car after being affected by friction
	///
	/// \see Neutral
	/// \see ReversingAccel
	///
	////////////////////////////////////////////////////////////

	void Accelerate(); // Called if player accelerating
	////////////////////////////////////////////////////////////
	/// \brief Stops accelerating the car and due to the RPM dropping and friction occuring car will eventally reach standstill
	///
	/// \see Accelerate
	/// \see ReversingAccel
	///
	////////////////////////////////////////////////////////////
	void Neutral(); // Called if player is not accelerating

	////////////////////////////////////////////////////////////
	/// \brief Negetively accelerates the car by a constant after being affected by friction
	///
	/// \see Accelerate
	/// \see Neutral
	///
	////////////////////////////////////////////////////////////
	void ReversingAccel();

	////////////////////////////////////////////////////////////
	/// \brief Called if a player is attempting to turn. Turns car left or right depending on which key was pressed
	///
	/// 
	/// 
	///
	////////////////////////////////////////////////////////////
	void Turn();

	////////////////////////////////////////////////////////////
	/// \brief Manages the gear and RPM of the car which is used for acceleration.
	///
	//// \param timestep A float which holds gametime
	///
	/// \see m_iRPM
	/// \see m_iGear
	/// \see m_aiAccelRates
	/// \see  m_afGearRates
	/// \see Accelerate
	////////////////////////////////////////////////////////////
	void GearsManagement(float timestep);

	////////////////////////////////////////////////////////////
	/// \brief Sets the car's position to a given myVector
	///
	//// \param Pos A myVector to which the cars location will be set to
	///
	////////////////////////////////////////////////////////////
	void CarSetPos(myVector Pos);

	////////////////////////////////////////////////////////////
	/// \brief Allows car and wheels to be drawn to the screen
	///
	/// \param target Drawable to be drawn
	/// \param states States to be drawn
	///
	////////////////////////////////////////////////////////////
	void draw(RenderTarget & target, RenderStates states) const;

	////////////////////////////////////////////////////////////
	/// \brief Updates the variables that need to be updated every frame such as RPM, Steering angle, Tyre position, ect.
	///
	/// \param timestep Float game time
	///
	////////////////////////////////////////////////////////////
	void update(float timestep);

	////////////////////////////////////////////////////////////
	/// \brief Sets the texture to the car sprite from the texture loader
	///
	/// Iterator is dereferenced to get texture
	/// \param GivenTexture A iterator of textures in a vector
	///
	////////////////////////////////////////////////////////////
	void setCarTexture(vector<Texture>::iterator GivenTexture);

	////////////////////////////////////////////////////////////
	/// \brief Polymorphic function derived from collidable class which takes any collidable and allows it to collide with any other collidable. In this case a Car and a tyre. 
	///
	/// \param B A tyre collidable to be collided with
	///
	////////////////////////////////////////////////////////////
	void Collide(Tyre* B);
	
	////////////////////////////////////////////////////////////
	/// \brief Returns the position of the car as a vector2f
	///
	/// \return Vector2f Location of the car
	///
	////////////////////////////////////////////////////////////
	Vector2f ReturnCarPos();
};

#endif

////////////////////////////////////////////////////////////
/// \class Car
///
/// Car is class which holds all infomation about the vehicle the player
/// drives in the game. To be instantiated it needs to be given a position, inverse mass and
/// starting velocity.
/// 
/// The class also handles the state of the car as in Accelerating, Neutral or Reversing
/// by checking what gear the car is in. Gear 0 is neutral and gear -1 is reversing while all positive gears are acceleration.
/// While accelerating the gears are managed in the gear management function which makes sure the gears are incremented realsiticly
/// when a certain RPM in each gear is reached. This creates a more realistic feeling car.
/// 
/// The car features a bicycle method of steering which means that the rotation of the car is based on the position of the wheels.
/// This system has its limitations but definitely has its limitations aspecially when it comes to side collisions but it helps 
///
/// Car is also a collidable, which means that it can collide with any other collidable. It is able to collide with m_Tyres using the
/// clamp method of circle-OBB collision. 
///
/// Usage example:
/// \code
/// m_Car = Car(myVector(2075, 65), myVector(0, 0), 0.3, myVector(0, 0));
/// \endcode
///
///
////////////////////////////////////////////////////////////