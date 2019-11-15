#include "OrangeGlow.h"

//constructor
OrangeGlow::OrangeGlow(Point newPos, int newSpeed, int newDamage, int newOrientation): Bullet(newPos, newSpeed, newDamage, newOrientation){
}

//destructor
OrangeGlow::~OrangeGlow(){
}

void OrangeGlow::render(SDL_Renderer* gRenderer, Point cameraPoint) {
       if (animation < 16)
                animation++;
        else
                animation = 0;
        
        SDL_Rect clip = { (32 * (animation % 4)), (32 * (animation / 4)), 32, 32 };

        DisplayManager::render(gRenderer, "../resources/blueBolt.png", this->position, cameraPoint, &clip, orientation, NULL, SDL_FLIP_NONE);
}

