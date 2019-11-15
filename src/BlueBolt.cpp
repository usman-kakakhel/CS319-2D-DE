#include "BlueBolt.h"

//constructor
BlueBolt::BlueBolt(Point newPos, int newSpeed, int newDamage, int newOrientation): Bullet(newPos, newSpeed, newDamage, newOrientation){
}

//destructor
BlueBolt::~BlueBolt(){
}

void BlueBolt::render(SDL_Renderer* gRenderer, Point cameraPoint) {
        if (animation < 16)
                animation++;
        else
                animation = 0;

        SDL_Rect clip = { (32 * animation), 0, 32, 64 };

        DisplayManager::render(gRenderer, "../resources/blueBolt.png", this->position, cameraPoint, &clip, orientation, NULL, SDL_FLIP_NONE);
}


