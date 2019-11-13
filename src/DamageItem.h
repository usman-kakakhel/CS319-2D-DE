#ifndef __DAMAGEITEM_H
#define __DAMAGEITEM_H

#include "Item.h"

class DamageItem : public Item{
public:
    DamageItem();
    ~DamageItem();
    string getName();
    void setName(string);

    // void render(SDL_Renderer* gRenderer, Point cameraPoint);
private:
    string name;
    string sprite = "../resources/health.png";
};

#endif