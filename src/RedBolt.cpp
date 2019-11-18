#include "RedBolt.h"

//constructor
RedBolt::RedBolt(Point newPos, int newSpeed, int newDamage, int newOrientation): Bullet(newPos, newSpeed, newDamage, newOrientation){
}

//destructor
RedBolt::~RedBolt(){
}

void RedBolt::render(SDL_Renderer* gRenderer, Point cameraPoint) {
       if (animation < 15)
                animation++;
        else
                animation = 0;
        
        SDL_Rect clip = { (32 * animation), 0, 32, 64 };

        DisplayManager::render(gRenderer, "../resources/redBolt.png", this->position, cameraPoint, &clip, orientation, NULL, SDL_FLIP_NONE);
}

