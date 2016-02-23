////////////////////////////////////////////////////////////
//
// Car Game - Created by Egor Kharlamov
// Created for C++ Year 2 Coursework at DMU - Games Programming Course
//
// This project is a racing game which contains realistic car physics and polymorphic impulse resolution 
//
////////////////////////////////////////////////////////////
#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class TextureLoader
{
private:
	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	vector<Texture> textures;///< A vector of textures which all textures used in the program should be loaded into.
	string m_sBaseDirectory;///< A string holding a base directory to find textures
	Texture m_Holder; ///< A tempary m_Holder of a texture before it is added to the vector of textures;

public:
	////////////////////////////////////////////////////////////
	/// \brief Default constructor
	///
	/// Initialises the Texture Loader
	///
	////////////////////////////////////////////////////////////
	TextureLoader();

	////////////////////////////////////////////////////////////
	/// \brief Allows the base directory which the textures are loaded from to be changed.
	///
	/// \param dir The new base directory
	///
	////////////////////////////////////////////////////////////
	void setBaseDirectory(string dir);

	////////////////////////////////////////////////////////////
	/// \brief Function where all necessary textures should be loaded in.
	///
	/// \see m_Holder
	/// \see m_sBaseDirectory
	/// \see textures
	///
	////////////////////////////////////////////////////////////
	void load();

	////////////////////////////////////////////////////////////
	/// \brief Allows textures from the Texture Loader to be used for sprite in other classes
	///
	/// \param index Which texture is wanted
	///
	/// \returns The texture from the index
	///
	////////////////////////////////////////////////////////////
	vector<Texture>::iterator getTextureIterator(int index);
};

#endif


////////////////////////////////////////////////////////////
/// \class TextureLoader  
///
/// The Texture Loader makes loading in textures far more efficient as a 
/// new texture doesn't need to be loaded in everytime a new instance of something
/// is created. 
/// 
/// All textures need to be loaded in once into the textures vector and then
/// they can all be accessed by any class thats needs them by getting the texture Iterator
/// 
///
/// Usage example:
/// \code
/// void Car::setCarTexture(vector<Texture>::iterator GivenTexture)
///{
///	m_render.setTexture(*GivenTexture);
///}
/// \endcode
///
///
////////////////////////////////////////////////////////////