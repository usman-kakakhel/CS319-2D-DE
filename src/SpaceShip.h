#ifndef __SPACESHIP_H
#define __SPACESHIP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>


#include "DisplayManager.h"
#include "MyEnums.h"
#include "Point.h"
#include "Camera.h"
#include "TargetedWeapon.h"
#include "BlueBolt.h"


class SpaceShip : public DisplayManager{
    public:
        SpaceShip();
        ~SpaceShip();
        Point getPoint();
        int getHealthStatus();
        int getFuelStatus();
        int getMissileCountdown();
        int getClearScreenCountdown();
        void setPoint(Point myPoint);
        Orientation getOrientation();
        void setOrientation(Orientation orientation);
        void updatePosition();
        void fireBullet(TargetedWeapon** &weaponList, int &size);

        void render(SDL_Renderer* gRenderer, Point cameraPoint);
        
    private:
        Point myPoint;
        bool isMoving;
        int healthStatus = 100;
        int fuelStatus = 100;
        int speed = 30;
        int clearScreenCountdown = 3;
        int missileCountdown = 3;
        int fireAnimation = 0;
        Orientation orientation;
        Orientation prevOrientation;
        string spriteList[3] = {"../resources/right.png", "../resources/up.png", "../resources/down.png"};

};

#endif