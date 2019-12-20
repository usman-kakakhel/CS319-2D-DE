#include "Button.h"

Button::Button(Point position, string sprite){
    this->position = position;
    this->buttonSprite = sprite;

    mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(buttonSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);

    //Load sound effects
    shortSound = Mix_LoadWAV( "../resources/Sounds/click.wav" );
    if( shortSound == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}
Button::~Button(){
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

void Button::render(){
    DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, position, 0, NULL, 0, NULL, SDL_FLIP_NONE);
}

bool Button::isPressed(Point* pressPoint){
    if (pressPoint == NULL)
        return false;
    if (pressPoint->getX() >= position.getX() && pressPoint->getX() <= position.getX() + mCTexture->mWidth &&
        pressPoint->getY() >= position.getY() && pressPoint->getY() <= position.getY() + mCTexture->mHeight){
            if (shortSound != NULL)
                Mix_PlayChannel( -1, shortSound, 0 );
            return true;
        }
        
    return false;
}


 Point Button::getPosition(){
     return position;
 }