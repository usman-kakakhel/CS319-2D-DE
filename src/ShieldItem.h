#ifndef __SHIELDITEM_H
#define __SHIELDITEM_H

#include "Item.h"

class ShieldItem : public Item {
public:
    ShieldItem();
    ~ShieldItem();
    string getName();
    void setName(string);

    void render(SDL_Renderer* gRenderer, Point cameraPoint);
private:
    string name;
    string sprite = "../resources/shield.png";
};

#endif