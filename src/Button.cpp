/*
Button Class
This class implements all the buttons used in the game. Each selection in any of the menus is a button, e.g. Start New Game, Resume...
*/
#include "Button.h"

// Constructor with posititon and a different sprite for the different button used
Button::Button(Point position, string sprite){
    this->position = position;
    this->buttonSprite = sprite;

	// Texture of the button
    mCTexture = new DisplayManager::CustomTexture();
    DisplayManager::loadFromFile(buttonSprite, mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight);

    //Load sound effects
    shortSound = Mix_LoadWAV( "../resources/Sounds/click.wav" );
    if( shortSound == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}
// Destructor for button
Button::~Button(){
	// Delete the textures
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
// Render the button
void Button::render(){
    DisplayManager::render(mCTexture->mTexture, mCTexture->mWidth, mCTexture->mHeight, position, 0, NULL, 0, NULL, SDL_FLIP_NONE);
}

// Return whether the button is pressed or not. Crucial for all buttons
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

// Return the position of the button
Point Button::getPosition(){
     return position;
}
