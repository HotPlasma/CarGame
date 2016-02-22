////////////////////////////////////////////////////////////
//
// Car Game - Created by Egor Kharlamov
// Created for C++ Year 2 Coursework at DMU - Games Programming Course
//
// This project is a racing game which contains realistic car physics and polymorphic impulse resolution 
//
////////////////////////////////////////////////////////////
#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Vector.h>

using namespace std;
using namespace sf;

class HUD : public Drawable
{
private:
	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	RectangleShape m_needle;///< The RectangleShape which represents the needle for the RPM counter
	Sprite RPMSprite;///< The RPM counter on the Heads Up Display
	Font DigiFont;///< Electronic font
	Text GearText;///< The text that displays on the RPM counter and dispays the current gear the car is in
	Text TimerText;///< Holds the current laptime. Will get reset when a lap is completed
	float BestTime; ///< Holds the current best laptime the track has been completed in
	Clock m_timer; ///< sf::Clock which times the laps
	Text BestTimeText; ///< Used to display the best laptime ton the screen
public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Initialises a HUD.
	///
	////////////////////////////////////////////////////////////
	HUD();
	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	FloatRect StartLine;///< Float Rect used to mark the start line during the race
	FloatRect MidLine;///< Float Rect used to make the mid line during the race

	////////////////////////////////////////////////////////////
	/// \brief Allows car and wheels to be drawn to the screen
	///
	/// \param target Drawable to be drawn
	/// \param states States to be drawn
	///
	////////////////////////////////////////////////////////////
	void draw(RenderTarget& target, RenderStates states) const;

	////////////////////////////////////////////////////////////
	/// \brief Keeps the needle pointing at the correct reading on the RPM counter
	///
	/// \param rpm The RPM the needles position will be based on
	///
	/// \see m_needle
	///
	////////////////////////////////////////////////////////////
	void updateNeedle(int rpm);

	////////////////////////////////////////////////////////////
	/// \brief Keeps the Gear text updated depending on the gear the car is in.
	///
	/// \param gear Used to set the text of GearText
	/// 
	/// \see GearText
	///
	////////////////////////////////////////////////////////////
	void updateGear(int gear);

	////////////////////////////////////////////////////////////
	/// \brief Gets the position of the RPM counter.
	///
	/// \return A Vector2f of the position of the RPM counter
	/// 
	/// \see RPMSprite
	///
	////////////////////////////////////////////////////////////
	Vector2f getRPMCounterPos();

	////////////////////////////////////////////////////////////
	/// \brief Sets the texture to the RPM sprite from the texture loader
	///
	/// Iterator is dereferenced to get texture
	///
	/// \param GivenTexture A iterator of textures in a vector
	///
	////////////////////////////////////////////////////////////
	void SetRPMTexture(vector<Texture>::iterator GivenTexture);

	////////////////////////////////////////////////////////////
	/// \brief Keeps the time text updated. Needs to be run every frame from game.
	///
	///
	/// \see TimerText
	/// \see m_timer
	///
	////////////////////////////////////////////////////////////
	void updateTimers();

	////////////////////////////////////////////////////////////
	/// \brief Resets the m_timer
	///
	///
	/// \see TimerText
	/// \see m_timer
	///
	////////////////////////////////////////////////////////////
	void ResetTimer();

	////////////////////////////////////////////////////////////
	/// \brief Updates the best time with the time in m_timer.
	///
	///
	/// Should only be run if best time was beaten
	///
	///
	/// \see TimerText
	/// \see m_timer
	/// \see BestTime
	/// \see BestTimeText
	///
	////////////////////////////////////////////////////////////
	void UpdateBestTime();
};

#endif

////////////////////////////////////////////////////////////
/// \class HUD
///
/// HUD (Heads Up Display) is a class which manages all the infomation the player
/// needs to know in order to play the game. It creates the RPM counter, gear counter and 
/// lap and best time counter.
/// 
/// HUD also ensures the gear values and needle position are correct and to the actions
/// of the car. 
/// 
/// HUD also manages the checkpoints for the lap times. The checkpoints are float rects which 
/// can be collided with in the Game class which would then in turn give the infomation to update
/// the timer or best time
///
/// Usage example:
/// \code
/// HUD();
/// \endcode
///
///
////////////////////////////////////////////////////////////
