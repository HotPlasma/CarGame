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
public:
	Game();
	Car m_Car;
	HUD m_Spedo;
	vector<Tyre*> Tyres;
	Tyre Tyre1;
	Tyre Tyre2;
	Tyre Tyre3;
	TextureLoader TexLoader;
	Sprite MapSprite;
	Texture MapTexture;
	void CreatePlayerCar();
	void CreateObstacles();
	void CreateTrack();
	void CreateTyre(Vector2f Position);
	void draw(RenderTarget &target, RenderStates states) const;
	void update(float timestep);
	void processKeyPress(Keyboard::Key code);
	void processKeyRelease(Keyboard::Key code);
	void generateMap(vector<Texture>::iterator GivenTexture);
	void saveTyrePosToFile();
	void loadTyrePosFromFile();
	Vector2f GetCarPos();
	Vector2f GetRPMCounterPos();
};


#endif