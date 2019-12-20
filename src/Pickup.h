#ifndef __PICKUP_H
#define __PICKUP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "DisplayManager.h"
#include "MyEnums.h"
#include "Point.h"
#include "Camera.h"

class Pickup {
public:
    //constructor and destructor
    Pickup(Point newPos, int newAmount);
    virtual ~Pickup();

    //getter and setter methods
    Point getPosition();
    void setPosition(Point thePoint);
    int getAmount();
    void setAmount(int myAmount);
    bool getToBeDestroyed();
    void setToBeDestroyed(bool toBeDestroyed);

    virtual int getWidth();
    virtual int getHeight();
    virtual void render(Point cameraPoint);

protected:
    Point position;
    int amount;
    bool toBeDestroyed = false;
};

#endif
