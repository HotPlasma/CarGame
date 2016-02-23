////////////////////////////////////////////////////////////
///
/// \mainpage Car Game - Created by Egor Kharlamov
/// Created for C++ Year 2 Coursework at DMU - Games Programming Course
///
/// This project is a racing game which contains realistic car physics and polymorphic impulse resolution.
/// 
/// This documentation follows all of the objects and their variables and functions
/// within the code.
/// 
/// Please use task bar to above to navigate.
////////////////////////////////////////////////////////////
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <Car.h>
#include <HUD.h>
#include <Tyre.h>
#include <TextureLoader.h>
#include <fstream>

using namespace sf;

class Game : public Drawable
{
private:
	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	Car m_Car;///< The instance of the car in Game
	vector<Tyre*> m_Tyres;///< Vector containing all m_Tyres that need to be drawn
	TextureLoader m_TexLoader; ///< TextureLoader instance used for loading in textures
	Sprite m_MapSprite;///< Sprite to hold the map
	bool m_bMidPassed = false; ///< Boolean used to keep track on wether the player has reached the mid point of the race
public:
	HUD m_HUD; ///< Instance of the HUD used for the UI

	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Creates a Game.
	/// This includes instantiating a car and a map
	///
	////////////////////////////////////////////////////////////
	Game();

	////////////////////////////////////////////////////////////
	/// \brief Creates a tyre in a given position
	///
	/// \param Position The position the tyre will be created in
	///
	/// Used to create m_Tyres by clicking. I use this generate my map. Tyre positions are added to
	/// a .txt file and are loaded in. 
	///
	/// \see m_Tyres
	/// \see SaveTyrePosToFile()
	/// \see loadTyrePosFromFile()
	///
	////////////////////////////////////////////////////////////
	void createTyre(Vector2f Position);

	////////////////////////////////////////////////////////////
	/// \brief Draws all drawables to the screen when game is drawn in main
	///
	/// \param target Drawable to be drawn
	/// \param states States to be drawn
	///
	////////////////////////////////////////////////////////////
	void draw(RenderTarget &target, RenderStates states) const;

	////////////////////////////////////////////////////////////
	/// \brief Updates the variables that need to be updated every frame.
	///
	/// \param timestep Float game time
	///
	////////////////////////////////////////////////////////////
	void update(float timestep);

	////////////////////////////////////////////////////////////
	/// \brief Function that takes key presses from main and processes them
	///
	/// Used for telling the car when to accelerate, turn, ect
	/// \param code They key that was pressed 
	///
	////////////////////////////////////////////////////////////
	void processKeyPress(Keyboard::Key code);

	////////////////////////////////////////////////////////////
	/// \brief Function that takes key releases from main and processes them
	///
	/// Used for telling the car when to stop accelerating, turning, ect
	/// \param code They key that was released 
	///
	////////////////////////////////////////////////////////////
	void processKeyRelease(Keyboard::Key code);

	////////////////////////////////////////////////////////////
	/// \brief Sets the texture to the Map sprite from the texture loader
	///
	/// Iterator is dereferenced to get texture
	/// \param GivenTexture A iterator of textures in a vector
	///
	////////////////////////////////////////////////////////////
	void generateMap(vector<Texture>::iterator GivenTexture);

	////////////////////////////////////////////////////////////
	/// \brief Saves the position of m_Tyres into a .txt file so I can generate obsticles around any map
	///
	/// \see m_Tyres
	/// \see createTyre
	///
	////////////////////////////////////////////////////////////
	void saveTyrePosToFile();

	////////////////////////////////////////////////////////////
	/// \brief Loads all the m_Tyres from a .txt 
	///
	/// Allows me to create boundaries for any map of any shape then save them to be loaded
	/// \see m_Tyres
	/// \see createTyre
	///
	////////////////////////////////////////////////////////////
	void loadTyrePosFromFile();

	////////////////////////////////////////////////////////////
	/// \brief Gets the cars position as a Vector2f
	///
	/// \return The position of the car as Vector2f
	/// 
	/// 
	///
	////////////////////////////////////////////////////////////
	Vector2f getCarPos();

	////////////////////////////////////////////////////////////
	/// \brief Gets the RPM counters position as a Vector2f
	///
	/// \return The position of the RPM counter as Vector2f
	/// 
	/// 
	///
	////////////////////////////////////////////////////////////
	Vector2f getRPMCounterPos();
};


#endif

////////////////////////////////////////////////////////////
/// \class Game
///
/// Game is absolutely essential to the game. It pulls together all of the other classes and makes
/// them function with eachother in order to maken this game playable.
/// 
/// Game is in charge of assigning textures and drawing everything to the screen and deciding on when a player
/// is accelerating or breaking. It also ensures that all the gears and RPM values change in order
/// to create realistic driving and movement.
/// 
/// Game proccesses all the keyboard controls and makes sure the game responds to player input. On top
/// of this Game ensures collisions are checked by everything and tells what functions need to be run in order to resolve the collisions.
/// 
/// Game is in charge of loading in the map from the texture loader for the player to race on.
/// 
/// Game also handles I/O in the form of reading tyre positions from a file and creating and drawing them to the screen.
///
///
////////////////////////////////////////////////////////////