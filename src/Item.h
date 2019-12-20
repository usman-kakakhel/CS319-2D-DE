#ifndef __ITEM_H
#define __ITEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "DisplayManager.h"

class Item {
public:
    Item(int amount, int price);
    ~Item();
    int getAmount();
    int getPrice();
    bool getBought();
    void setPrice(int price);
    void setAmount(int amount);
    void setBought(bool bought);

private:
    int amount;
    int price;
    bool bought;
};

#endif
