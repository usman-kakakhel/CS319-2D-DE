#ifndef __ENEMY_H
#define __ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cmath>


#include "DisplayManager.h"
#include "MyEnums.h"
#include "Point.h"
#include "Camera.h"

class Enemy : public DisplayManager{
    public:
        Enemy();
        ~Enemy();
        Point getPoint();
        void setPoint(Point myPoint);
        void updatePosition(Point spaceShipPos);
        void render(SDL_Renderer* gRenderer, Point cameraPoint);
    private:
        Point myPoint;
        int speed = 5;
        int followAccuracy = 2;
        string spritePath = "../resources/enemy.png";       
};

#endif
