/*
BlueBolt Class Header
This class implements the blueBolt bullet of the game. BlueBolt is the bullet which the player's spaceship  can shoot by pressing button 'z'.
*/
#ifndef __BLUEBOLT_H
#define __BLUEBOLT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Bullet.h"

// Inherits Bullet because blueBolt is a bullet initially
class BlueBolt : public Bullet{
public:
	// Constructor requires the point of the bullet, its speed, damage, and orientation of it.
	BlueBolt(Point newPos, int newSpeed, int newDamage, int newOrientation);
	~BlueBolt() override;	// Override the Bullet's destructor
	int getWidth() override;	// Override the Bullet's getWidth method
	int getHeight() override;	// Override the Bullet's getHeight method
	void render( Point CameraPoint) override;	// Override the Bullet's render method
	
private:
	//textures and image addresses
	DisplayManager::CustomTexture* mCTexture = NULL;
	string blueSprite = "../resources/blueBolt.png";
};

#endif

