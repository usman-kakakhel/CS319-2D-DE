#ifndef __DISPLAYMANAGER_H
#define __DISPLAYMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Point.h"

using namespace std;

class DisplayManager{
    public:
        ~DisplayManager();
        static bool loadFromFile(string path, SDL_Texture* &mTexture, int &mWidth, int &mHeight);
        static Point getRenderPointFor(Point thePoint, Point cameraPoint);
        static void render(SDL_Texture* mTexture, int mWidth, int mHeight, Point thePoint, Point cameraPoint, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
        static void renderText(string text, Point thePoint);
    
        static int SCREEN_WIDTH;
        static int SCREEN_HEIGHT;
        static int GAME_WIDTH;

        static SDL_Renderer* gRenderer;
        static TTF_Font* lazy;

        struct CustomTexture{
            SDL_Texture* mTexture = NULL;
            int mWidth = 0;
            int mHeight = 0;
        };
        typedef struct CustomTexture CustomTexture;
        

    private:
        DisplayManager();
        
};

#endif