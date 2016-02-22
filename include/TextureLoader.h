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
	string baseDirectory;///< A string holding a base directory to find textures
	Texture Holder; ///< A tempary holder of a texture before it is added to the vector of textures;

public:
	TextureLoader();
	void setBaseDirectory(string dir);
	void load();
	vector<Texture>::iterator getTextureIterator(int index);
};

#endif