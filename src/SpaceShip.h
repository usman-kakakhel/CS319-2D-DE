#ifndef __SPACESHIP_H
#define __SPACESHIP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>


#include "DisplayManager.h"
#include "MyEnums.h"
#include "Point.h"
#include "Camera.h"


class SpaceShip : public DisplayManager{
    public:
        SpaceShip();
        ~SpaceShip();
        Point getPoint();
        void setPoint(Point myPoint);
        Orientation getOrientation();
        void setOrientation(Orientation orientation);
        void updatePosition();

        void render(SDL_Renderer* gRenderer, Point cameraPoint);
        
    private:
        Point myPoint;
        int speed = 30;
        Orientation orientation;
        Orientation prevOrientation;
        string spriteList[3] = {"../resources/right.png", "../resources/up.png", "../resources/down.png"};

};

#endif