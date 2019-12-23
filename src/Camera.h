/*
Camera Class
This class implements the camera class which shows the current view of the screen and follows the spaceship
*/
#ifndef __CAMERA_H
#define __CAMERA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "DisplayManager.h"
#include "Point.h"
#include "SpaceShip.h"
#include "MyEnums.h"
#include "Human.h"
#include "Enemy.h"
#include "MapView.h"

class Camera{
public:
    Camera();
    ~Camera();
    
    Point getPoint();
    void setPoint(Point myPoint);
    void render(int health, int fuel, int coin, int score, int missileCountdown, int clearScreenCountdown);
    void updateCameraPosition(Point shipInitialPoint, Point shipFinalPoint);
    void updateMap(SpaceShip* spaceShip, Enemy** enemyList, int enemyListSize, Human* humanList, int humanListSize);
    void showGameOver();

    //new methods to set and get highscore
    void setHighScore(int value);
    int getHighScore();
    
private:
    Point myPoint;
    Point* backgroundPosStart;
    int numOfHills;
    int highScore = 0;
    MapView* mapView;

    //textures and image addresses
    string spriteList[7] = {"../resources/health.png", "../resources/fuel.png", "../resources/coin.png", "../resources/score.png","../resources/highScore.png", "../resources/missile.png" ,"../resources/massBomb.png"};
    string background = "../resources/background.jpg";
    string ground = "../resources/ground.png";
    string gOver = "../resources/gameOver.png";
    DisplayManager::CustomTexture** mCTextureList = NULL;
    DisplayManager::CustomTexture* mCTextureBG = NULL;
    DisplayManager::CustomTexture* mCTextureGround = NULL;
    DisplayManager::CustomTexture* mCTextureGameOver = NULL;
};

#endif
