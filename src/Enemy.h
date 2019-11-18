#ifndef __ENEMY_H
#define __ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cmath>
#define PI 3.14159265


#include "DisplayManager.h"
#include "MyEnums.h"
#include "Point.h"
#include "Camera.h"
#include "TargetedWeapon.h"
#include "RedBolt.h"

class Enemy : public DisplayManager{
    public:
        //Enemy(Point newPos, int newSpeed , int newOrientation , TargetedWeapon** &weaponList, int &size, Point const &spaceShipPos );
        Enemy(Point newPos, int newSpeed , int newOrientation);
        ~Enemy();
        Point getPoint() const;
        void setPoint(Point myPoint);
        virtual void updatePosition(Point spaceShipPos);
        virtual void render(SDL_Renderer* gRenderer, Point cameraPoint);
        // virtual void fireWeapon(TargetedWeapon** &weaponList, int &size, Point &spaceShipPos);
        // void setTimer(TargetedWeapon*** weaponList, int* size, Point* spaceShipPos);
        
    protected:
        Point myPoint;
        int speed;
        int orientation;
        int followAccuracy = 2; 
        //SDL_TimerID timerID;   
};

#endif