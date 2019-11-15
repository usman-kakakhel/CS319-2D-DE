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
    SDL_Rect renderQuad;
    if (clip == NULL){
        renderQuad = { point.getX(), point.getY(), mWidth, mHeight };
    }
    else{
        renderQuad = { point.getX(), point.getY(), clip->w, clip->h };
    }
        
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void DisplayManager::renderText(SDL_Renderer* gRenderer, string text, Point thePoint){
    clear();

    TTF_Font* lazy = TTF_OpenFont("../resources/lazy.ttf", 45);
    if( lazy == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        SDL_Color White = {255, 255, 255};  
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(lazy, text.c_str(), White); 
        if( surfaceMessage == NULL ){
            printf( "Unable to load message %s! SDL_ttl Error: %s\n", text.c_str(), TTF_GetError() );
        }
        else{
            mTexture = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage); 

            SDL_Rect Message_rect = {thePoint.getX(), thePoint.getY(), surfaceMessage->w, surfaceMessage->h}; 
            SDL_FreeSurface( surfaceMessage );

            SDL_RenderCopy(gRenderer, mTexture, NULL, &Message_rect); 
        }
    }
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