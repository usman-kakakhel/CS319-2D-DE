#ifndef __CAMERA_H
#define __CAMERA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "DisplayManager.h"
#include "Point.h"

class Camera : public DisplayManager{
    public:
        Camera();
        ~Camera();
        
        Point getPoint();
        void setPoint(Point myPoint);
        void render(SDL_Renderer* gRenderer, int health, int fuel, int coin, int score, int highScore, int missileCountdown, int clearScreenCountdown);

        void updateCameraPosition(Point shipInitialPoint, Point shipFinalPoint);
        
    private:
        Point myPoint;
        Point* backgroundPosStart;
        int numOfHills;
        string spriteList[7] = {"../resources/health.png", "../resources/fuel.png", "../resources/coin.png", "../resources/score.png","../resources/highScore.png", "../resources/missile.png" ,"../resources/massBomb.png"};
};


#endif