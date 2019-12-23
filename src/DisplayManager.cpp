/*
DisplayManager Class
This class implements the displaying of any object which needs to be rendered or shown in the screen
*/
#include "DisplayManager.h"

// Default values of the screen will be initialized
int DisplayManager::SCREEN_WIDTH = 1920;
int DisplayManager::SCREEN_HEIGHT = 1080;
int DisplayManager::GAME_WIDTH = 5760;

SDL_Renderer* DisplayManager::gRenderer = NULL;
TTF_Font* DisplayManager::lazy = NULL;

// Constructor and Destructor not needed
DisplayManager::DisplayManager(){
}
DisplayManager::~DisplayManager(){
}

// Get the rendering point for the given position
Point DisplayManager::getRenderPointFor(Point thePoint, Point cameraPoint){
    thePoint.setX(thePoint.getX() - cameraPoint.getX());
    return thePoint;
}

// Render the given texture
void DisplayManager::render(SDL_Texture* mTexture, int mWidth, int mHeight, Point thePoint, Point cameraPoint, SDL_Rect* clip, double angle, 	SDL_Point* center, SDL_RendererFlip flip){
    Point point = getRenderPointFor(thePoint, cameraPoint);

    SDL_Rect renderQuad;
    if (clip == NULL){
        renderQuad = { point.getX(), point.getY(), mWidth, mHeight };
    }
    else{
        renderQuad = { point.getX(), point.getY(), clip->w, clip->h };
    }
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void DisplayManager::renderText(string text, Point thePoint){
    if( lazy != NULL )
    {
        SDL_Color White = {255, 255, 255};  
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(lazy, text.c_str(), White); 
        if( surfaceMessage == NULL ){
            printf( "Unable to load message %s! SDL_ttl Error: %s\n", text.c_str(), TTF_GetError() );
        }
        else {
            SDL_Texture* mTexture = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage); 

            SDL_Rect Message_rect = {thePoint.getX(), thePoint.getY(), surfaceMessage->w, surfaceMessage->h}; 
            SDL_FreeSurface( surfaceMessage );

            SDL_RenderCopy(gRenderer, mTexture, NULL, &Message_rect);
            SDL_DestroyTexture( mTexture );
        }
    }
}

// Load the sprite from the path and put it in the given texture
bool DisplayManager::loadFromFile(string path, SDL_Texture* &mTexture, int &mWidth, int &mHeight){

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ){
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else {
        //color key gets the color in the rgb and sets it to transparent
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        mTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( mTexture == NULL ){
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else{
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    return (mTexture != NULL);
}

