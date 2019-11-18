#ifndef __HUMAN_H
#define __HUMAN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "DisplayManager.h"
#include "MyEnums.h"
#include "Point.h"
#include "Camera.h"

class Human : public DisplayManager {
public:
    Human(Point thePoint = {0,0});
    ~Human();
    // Orientation getOrientation();
    // void setOrientation(Orientation newOrient);
    bool getState();
    void setState(bool newState);
    Point getPosition();
    void setPosition(Point thePoint);

    void render(SDL_Renderer* gRenderer, Point cameraPoint);

private:
    Point position;
    bool state;
    // Orientation orientation;
    string sprite = "../resources/human.png";
};

#endif