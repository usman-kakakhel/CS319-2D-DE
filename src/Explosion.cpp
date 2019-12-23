/*
Explosion class
This class implements the explosion event when the enemies are killed/shot by the spaceship
*/
#include "Explosion.h"

// Constructor which creates an instance of explosion at the point given(enemy point)
Explosion::Explosion(Point thePoint){
    pos = thePoint;
    //make textures
    mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(warpSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);

    //Load sound effects
    shortSound = Mix_LoadWAV( "../resources/Sounds/explosion.wav" );
    if( shortSound == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
	if (shortSound != NULL)
		Mix_PlayChannel( -1, shortSound, 0 );
}
Explosion::~Explosion(){
    if (mCTexture != NULL){
        delete mCTexture->mTexture;
        delete mCTexture;
    }
    if (shortSound != NULL){
        //Free the sound effects
        Mix_FreeChunk( shortSound);
        shortSound = NULL;
    }
}
Point Explosion::getPos(){
    return pos;
}
void Explosion::setPos(Point thePoint){
    pos = thePoint;
}
int Explosion::getWidth(){
    return mCTexture->mWidth;
}
int Explosion::getHeight(){
    return mCTexture->mHeight;
}
bool Explosion::getToBeDestroyed(){
    return toBeDestroyed;
}
void Explosion::setToBeDestroyed(bool toBeDestroyed){
    this->toBeDestroyed = toBeDestroyed;
}

// Render the explosion in the given cameraPoint
void Explosion::render( Point cameraPoint){
    if (animation < 40)
        animation++;
    else
        toBeDestroyed = true;
    
    SDL_Rect clip = { (128 * animation), 0, 128, 128 };

    DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, pos, cameraPoint, &clip, 0, NULL, SDL_FLIP_HORIZONTAL);
}

// Assignement operator override
void Explosion::operator=(Explosion const &theExplosion){
    animation = theExplosion.animation;
    pos = theExplosion.pos;
    toBeDestroyed = theExplosion.toBeDestroyed;
}
