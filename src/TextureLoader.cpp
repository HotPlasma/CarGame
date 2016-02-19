#include <TextureLoader.h>

TextureLoader::TextureLoader()
{
	baseDirectory = "..\\assets\\"; //Default base directory
	load();
}


void TextureLoader::setBaseDirectory(string dir) // Allows base directory to be changed if neccessary
{
	baseDirectory = dir;
}

void TextureLoader::load() // Loads in all needed textures and adds them to the textures vector
{

	vector<string>fileNames;
	fileNames.push_back("HUD\\RPM.png");
	fileNames.push_back("Sprites\\Tyre.png");
	fileNames.push_back("Maps\\Track.png");
	fileNames.push_back("Sprites\\Car.png");

	for (int i = 0; i < fileNames.size(); i++)
	{
		if (!Holder.loadFromFile(baseDirectory + fileNames.at(i)))
		{
			cout << "Could not load " << fileNames.at(i) << endl;
		}
		textures.push_back(Holder);
	}
}

vector<Texture>::iterator TextureLoader::getTextureIterator(int index) //Allows the assigning of textures to sprites
{
	return vector<Texture>::iterator(textures.begin() + index);
}