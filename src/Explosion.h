#ifndef __EXPLOSION_H
#define __EXPLOSION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>

#include "DisplayManager.h"
#include "MyEnums.h"
#include "Point.h"

class Explosion{
public:
    Explosion(Point thePoint = {0,0});
    ~Explosion();
    Point getPos();
    void setPos(Point thePoint);
    int getWidth();
    int getHeight();
    bool getToBeDestroyed();
    void setToBeDestroyed(bool toBeDestroyed);

    void operator=(Explosion const &theExplosion);

    void render( Point cameraPoint);

private:
    int animation = 0;
    Point pos;     // Initial position of a explosion
    bool toBeDestroyed = false;

    Mix_Chunk* shortSound = NULL;
    //textures and image addresses
	DisplayManager::CustomTexture* mCTexture = NULL;
    string warpSprite = "../resources/explosion.png"; 
};

#endif
