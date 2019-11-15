#ifndef __WEAPON_H
#define __WEAPON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "DisplayManager.h"


class Weapon : public DisplayManager{
    public:
        Weapon();
        ~Weapon();
};

#endif


