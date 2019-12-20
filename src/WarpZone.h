#ifndef __WARPZONE_H
#define __WARPZONE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "DisplayManager.h"
#include "MyEnums.h"
#include "Point.h"
#include "Camera.h"

class WarpZone{
public:
    WarpZone(Point startPoint = {0,0}, Point endPoint = {0,0});
    ~WarpZone();
    Point getStartPos();
    void setStartPos(int x, int y);
    Point getEndPos();
    void setEndPos(int x, int y);
    int getWidth();
    int getHeight();
    bool getToBeDestroyed();
    void setToBeDestroyed(bool toBeDestroyed);

    void render( Point cameraPoint);

private:
    int animation = 1;
    Point startPos;     // Initial position of a warpzone
    Point endPos;      // Position where the spaceship will be respawned at
    bool toBeDestroyed = false;
    //textures and image addresses
	DisplayManager::CustomTexture* mCTexture = NULL;
    string warpSprite = "../resources/warpzone.png";        // Sprite of the warpzone loaded from resources folder
};

#endif
