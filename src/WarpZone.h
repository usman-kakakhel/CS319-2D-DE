#ifndef __WARPZONE_H
#define __WARPZONE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "DisplayManager.h"
#include "MyEnums.h"
#include "Point.h"
#include "Camera.h"

class WarpZone : public DisplayManager {
public:
    WarpZone();
    ~WarpZone();
    Point getStartPos();
    void setStartPos(int x, int y);
    Point getEndPos();
    void setEndPos(int x, int y);

    void render(SDL_Renderer* gRenderer, Point cameraPoint);

private:
    Point startPos;     // Initial position of a warpzone
    Point endPos;      // Position where the spaceship will be respawned at
    string sprite = "../resources/warpzone.png";        // Sprite of the warpzone loaded from resources folder
};

#endif