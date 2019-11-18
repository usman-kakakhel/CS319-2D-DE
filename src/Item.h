#ifndef __ITEM_H
#define __ITEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "DisplayManager.h"

class Item : public DisplayManager {
public:
    Item();
    ~Item();
    int getPrice();
    void setPrice(int);

private:
    int price;
    bool bought;
};

#endif