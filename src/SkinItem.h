#ifndef __SKINITEM_H
#define __SKINITEM_H

#include "Item.h"

class SkinItem : public Item{
public:
    SkinItem();
    ~SkinItem();
    string getName();
    void setName(string);

    // void render(SDL_Renderer* gRenderer, Point cameraPoint);
private:
    string name;
    string sprite = "../resources/skin.png";
};

#endif