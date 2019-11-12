#include "DisplayManager.h"

DisplayManager::DisplayManager(){
    DisplayManager::mHeight = 0;
    DisplayManager::mWidth = 0;
}

DisplayManager::~DisplayManager(){
    clear();
}

Point DisplayManager::getRenderPointFor(Point thePoint, Point cameraPoint){
    thePoint.setX(thePoint.getX() - cameraPoint.getX());
    return thePoint;
}

void DisplayManager::render(SDL_Renderer* gRenderer, string path, Point thePoint, Point cameraPoint, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
    Point point = getRenderPointFor(thePoint, cameraPoint);

    DisplayManager::gRenderer = gRenderer;
    loadFromFile(path);
    SDL_Rect renderQuad = { point.getX(), point.getY(), mWidth, mHeight };
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

bool DisplayManager::loadFromFile(string path){
    //clear the already texture present in the mtexture
    clear();

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL ){
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else{
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

void DisplayManager::clear(){
    //if a texture exists remove it
    if( mTexture != NULL ){
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}