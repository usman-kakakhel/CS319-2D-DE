#ifndef __DISPLAYMANAGER_H
#define __DISPLAYMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

using namespace std;

class DisplayManager{
    public:
        DisplayManager();
        ~DisplayManager();
        bool loadFromFile(string path);
        void render(SDL_Renderer* gRenderer, string path, int x = 0, int y = 0, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
        void clear();
    private:
        SDL_Renderer* gRenderer = NULL;
        SDL_Texture* mTexture = NULL;

        int mWidth;
        int mHeight;
};

#endif