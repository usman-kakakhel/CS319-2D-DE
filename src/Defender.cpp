#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "GameFrame.h"
#include "EventListener.h"
#include "MyEnums.h"

//if you want to run on windows just remove the SDL/ from the headers

//attributes
int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;
int GAME_WIDTH = 5760;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Event e;


//methods required
bool init();
void close();
void handleEvent(GameFrame* myFrame, bool* keyList);




int main( int argc, char* args[] ){
    bool quit = false;
    GameFrame myFrame;
    EventListener listener;
    bool keyList[7];
    for (int i = 0; i < 7; i++){keyList[i] = false;}

	if( !init() ){ 
        printf( "Failed to initialize!\n" );
    }
    else{
        //game loop
        //Running untill quit pressed
        while(!quit){
            
            listener.getEvent(e, keyList, &quit);
            handleEvent(&myFrame, keyList);

            SDL_RenderClear( gRenderer ); //clearing the renderer for new renders
            //any updating textures to the renderer
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF ); //just checking by turning the renderer color to green.
            myFrame.updateUI(gRenderer);
            SDL_RenderPresent( gRenderer );
        }
    }
    
	return 0;
}


bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //creating an outer window
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        SCREEN_HEIGHT = DM.h;
        SCREEN_WIDTH = DM.w;
        GAME_WIDTH = SCREEN_WIDTH * 3;
        
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //the renderer on which textures will be updated
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            //just giving the renderer black colour
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            //initializing sdl images which will allow sprites to be loaded
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }

            if (TTF_Init() < 0){
                printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                success = false;
            }
        }
    }

    return success;
}

void handleEvent(GameFrame* myFrame, bool* keyList){
    if (keyList[UP_PRESSED]){
        myFrame->updateSpaceshipPosition(UP);
    }
    else if (keyList[DOWN_PRESSED]){
        myFrame->updateSpaceshipPosition(DOWN);
    }
    else if (keyList[LEFT_PRESSED]){
        myFrame->updateSpaceshipPosition(LEFT);
    }
    else if (keyList[RIGHT_PRESSED]){
        myFrame->updateSpaceshipPosition(RIGHT);
    }
    if (keyList[BULLET_KEY] || keyList[MISSILE_KEY] || keyList[DESTRUCTION_KEY]){
        myFrame->fire(keyList);
    }
}


void close()
{
    //pretty self explanatory
	SDL_DestroyRenderer( gRenderer);
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    TTF_Quit();
	IMG_Quit();
    SDL_Quit();
}