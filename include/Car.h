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
	Car();
	Car(myVector position, myVector acceleration, float invMass, myVector velocity);
	RectangleShape FrontWheel[2];
	RectangleShape RearWheel[2];
	void Accelerate(); // Called if player accelerating
	void Neutral(); // Called if player is not accelerating
	void ReversingAccel(); // Called if player is reversing
	void Turn();
	void GearsManagement(float timestep); // Manages gear changes and RPM
	void CarSetPos(myVector Pos);

	//Sets Rotation bool defaults
	bool RotatingRight = false;
	bool RotatingLeft = false;

	int m_iRPM;
	int m_iGear;
	int m_aiAccelRates[5];
	float m_aiGearRates[6];

	float m_fSteeringAngle;

	float m_fRotationAngle;
	myVector RotationVector;

	Sprite m_render;
	//Sprite m_carSprite;

	void draw(RenderTarget & target, RenderStates states) const;
	void update(float timestep);

	void setCarTexture(vector<Texture>::iterator GivenTexture);

	void Collide(Tyre* B);
	Texture CarTex;

	Vector2f ReturnCarPos();
};

#endif