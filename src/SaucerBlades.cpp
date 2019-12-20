#include "SaucerBlades.h"

SaucerBlades::SaucerBlades(Point newPos, int newSpeed, int newOrientation): Enemy(newPos, newSpeed, newOrientation){
    health = 50;
	FiringBehavior* firingBehavior = new FireRedBolt();
	Enemy::setFireBehavior(firingBehavior);

    mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(saucerSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);
}

SaucerBlades::~SaucerBlades(){
    if (mCTexture != NULL){
        delete mCTexture->mTexture;
        delete mCTexture;
    }
}


//enemy goes toward the ship
void SaucerBlades::updatePosition(Point spaceShipPos, Human* humanList, int size){
    
    myPoint.setX(myPoint.getX() + (speed * cos(orientation * PI /180)));
    myPoint.setY(myPoint.getY() + (speed * sin(orientation * PI /180)));

    if (myPoint.getX() <= (DisplayManager::SCREEN_HEIGHT / 8) || myPoint.getX() > DisplayManager::GAME_WIDTH - (DisplayManager::SCREEN_HEIGHT / 8)) {
        orientation = abs(180 - orientation);   
    }
    else if (myPoint.getY() < 170  || myPoint.getY() > DisplayManager::SCREEN_HEIGHT - (DisplayManager::SCREEN_HEIGHT / 5)) {
        if (myPoint.getY() <= 170){
            myPoint.setY(170 + speed);
        }
        else if(myPoint.getY() >= DisplayManager::SCREEN_HEIGHT - (DisplayManager::SCREEN_HEIGHT / 5)){
            myPoint.setY(DisplayManager::SCREEN_HEIGHT - (DisplayManager::SCREEN_HEIGHT / 5)  - speed);
        }
        orientation = abs(360 - orientation); 
    }

    
}

void SaucerBlades::fireWeapon(TargetedWeapon** &weaponList, int &size, Point spaceShipPos){
	Enemy::fireWeapon(weaponList, size, spaceShipPos);
}

void SaucerBlades::render( Point cameraPoint){
    if (animation < 15)
            animation++;
    else
            animation = 0;

    SDL_Rect clip = { (128 * animation), 0, 128, 128 };

    DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, this->myPoint, cameraPoint, &clip, 0, NULL, SDL_FLIP_NONE);
}

int SaucerBlades::getWidth() {
        return 128;
}

int SaucerBlades::getHeight() {
        return 128;
}
 
