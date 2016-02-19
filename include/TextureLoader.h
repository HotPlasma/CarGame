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
	vector<Texture> textures;
	string baseDirectory;
	Texture Holder;

public:
	TextureLoader();
	void setBaseDirectory(string dir);
	void load();
	vector<Texture>::iterator getTextureIterator(int index);
};

#endif