#ifndef __HUMAN_H
#define __HUMAN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "DisplayManager.h"
#include "MyEnums.h"
#include "Point.h"
#include <math.h>

class Human{
public:
    Human(Point thePoint = {0,0});
    ~Human();
    HumanState getState();
    void setState(HumanState newState);
    Point getPosition();
    void setPosition(Point thePoint);
    void setToBeDestroyed(bool toBeDestroyed);
    bool getToBeDestroyed();
    void updatePosition(Point spaceShipPosition, int spaceShipHeight, Point bugeyePosition, int bugeyeHeight);
    int getWidth();
    int getHeight();

    void render( Point cameraPoint);

    void operator=(Human const &myHuman);

private:
    Point position;
    HumanState state;
    bool toBeDestroyed = false;
    //textures and image addresses
    DisplayManager::CustomTexture* mCTexture = NULL;
    string humanSprite = "../resources/human.png";
};

#endif
