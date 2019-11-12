#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

#include "GameFrame.h"
#include "EventListener.h"
#include "MyEnums.h"

//if you want to run on windows just remove the SDL/ from the headers

//attributes
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
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
            SDL_SetRenderDrawColor( gRenderer, 0x21, 0xF5, 0x33, 0xFF ); //just checking by turning the renderer color to green.
            myFrame.updateUI(gRenderer);
            SDL_RenderPresent( gRenderer );
        }
    }
    
	return 0;
}


bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //creating an outer window
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
    if (keyList[BULLET_KEY]){
        
    }
    if (keyList[MISSILE_KEY]){
        
    }
    if (keyList[DESTRUCTION_KEY]){
        
    }
}


void close()
{
    //pretty self explanatory
	SDL_DestroyRenderer( gRenderer);
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

	IMG_Quit();
    SDL_Quit();
}