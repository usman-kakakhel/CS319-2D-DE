/*
Defender Class
This class is the most important class which has the main game instance in it.
*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

#include "ShopFrame.h"
#include "GameFrame.h"
#include "EventListener.h"
#include "MyEnums.h"
#include "DisplayManager.h"
#include "MenuFrame.h"
#include "Point.h"
#include "Item.h"

//if you want to run on windows just remove the SDL/ from the headers

//attributes
SDL_Window* gWindow = NULL;
SDL_Event e;

//semaphore for data buffer conflict resolution
SDL_sem* dataLock = NULL;

//sound effects and music
Mix_Music* menuMusic = NULL; //the music
Mix_Music* gameMusic = NULL; //the music
SoundState soundState;

//variables for main and runGameLoop
GameFrame* myFrame = NULL;
MenuFrame* menuFrame = NULL;
ShopFrame* shopFrame = NULL;

Point* clickLocation = NULL;
EventListener listener;
GameState state;
bool keyList[8];
Item** boughtHealthItems = NULL;
int boughtHealthItemsSize = 0;
Item** boughtFuelItems = NULL;
int boughtFuelItemsSize = 0;
int coins = 0;

//methods required
bool init();		// Initialize the SDL2 libararies
void close();		// Close the whole game and the SDL2 libraries
void runGameLoop();	// Game Loop
void timer_start(std::function<void(void)> func, unsigned int interval);	// Timer for the game, used later in setting the score


int main( int argc, char* args[] ){
    for (int i = 0; i < 7; i++){keyList[i] = false;}

	if( !init() ){ 
        printf( "Failed to initialize!\n" );
    }
    else{
        //since the first entity to encounter is main menu set initial state to main menu
        state = MAIN_MENU;
        //create the shop, game, and main menu frames
        menuFrame = new MenuFrame();
        myFrame = new GameFrame();
	shopFrame = new ShopFrame();

        //timer on another thread for backend GameFrame running
        timer_start(runGameLoop, 23);
        auto y = std::chrono::steady_clock::now();
        auto wait = std::chrono::steady_clock::now() + std::chrono::milliseconds(23);
        //Running until quit pressed
        while(state != QUIT){
            //adjusting the frame rate of the game
            std::this_thread::sleep_until(wait); 
            auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(23);   
            y = std::chrono::steady_clock::now();
            
            //if the state is main menu or pause then render the menu frame
            if (state == MAIN_MENU || state == PAUSE){
                //rendering the menu frame
                SDL_RenderClear( DisplayManager::gRenderer ); //clearing the renderer for new renders
                SDL_SetRenderDrawColor( DisplayManager::gRenderer, 0, 0, 0, 0 );
                menuFrame->update(clickLocation, &state);
                SDL_RenderPresent( DisplayManager::gRenderer ); //shwoing the renderer on screen
		Mix_Pause(1);
            }

            //if the state is shop, render the shop
            if (state == SHOP){
                //render shop
		SDL_RenderClear( DisplayManager::gRenderer );
                SDL_SetRenderDrawColor( DisplayManager::gRenderer, 0, 0, 0, 0 );
		shopFrame->update(clickLocation, &state, boughtHealthItems, boughtHealthItemsSize, boughtFuelItems, boughtFuelItemsSize, 				coins);
		SDL_RenderPresent( DisplayManager::gRenderer );
		Mix_Pause(1);
            }

            //if the state is resume, then play the game
            if (state == RESUME || state == GAME_OVER){
                SDL_RenderClear( DisplayManager::gRenderer ); //clearing the renderer for new renders
                //any updating textures to the renderer
                SDL_SemWait(dataLock); //wait for semaphore to allow update UI
                myFrame->updateUI(&state, coins);
                SDL_SemPost(dataLock);
                SDL_RenderPresent( DisplayManager::gRenderer ); //shwoing the renderer on screen
		if (state == GAME_OVER) 
			Mix_Pause(1);
            }
            //playing menuMusic
            //If there is no music playing
            if( Mix_PlayingMusic() == 0 )
            {
                if (state == MAIN_MENU || state == SHOP){
                    Mix_PlayMusic( menuMusic, -1 );
                    soundState = MENU;
                }
                else if(state == RESUME || state == GAME_OVER || state == PAUSE){
                    Mix_PlayMusic( gameMusic, -1 );
                    soundState = GAME;
                }  
            }
            //If music is being played
            else
            {
                if (soundState == MENU && (state == RESUME || state == GAME_OVER || state == PAUSE)){
                    Mix_HaltMusic();
                    Mix_PlayMusic( gameMusic, -1 );
                    soundState = GAME;
                }
                else if (soundState == GAME && (state == MAIN_MENU || state == SHOP)){
                    Mix_HaltMusic();
                    Mix_PlayMusic( menuMusic, -1 );
                    soundState = MENU;
                }
            }
            auto z = y - std::chrono::steady_clock::now();
            wait = x - z;
        }
    }
    close();		// Close once the gameLoop is done
	return 0;
}

// GameLoop method checks the state changes in the game
void runGameLoop(){
    listener.getEvent(e, keyList, &state, clickLocation);
    //if the state is new game, then remove all prev actors and create them again.
    if (state == NEW_GAME){
        myFrame->destroy();
        myFrame->init();
		shopFrame->destroy();
		shopFrame->init();
		coins = 0;
		myFrame->updateAllActors(keyList, &state, boughtHealthItems, boughtHealthItemsSize, boughtFuelItems, boughtFuelItemsSize, coins);
        state = RESUME;
    }
    //if state is resume then update all actors as normal
    else if (state == RESUME || state == GAME_OVER){
        if (state == RESUME){
            SDL_SemWait(dataLock);
            myFrame->updateAllActors(keyList, &state, boughtHealthItems, boughtHealthItemsSize, boughtFuelItems, boughtFuelItemsSize, coins);
            SDL_SemPost(dataLock);

		    for(int i = 0; i < boughtHealthItemsSize; i++) {
			if(boughtHealthItems[i] != NULL) {
				delete boughtHealthItems[i];
			}
	    }
	    delete [] boughtHealthItems;
	    boughtHealthItems = NULL;
	    boughtHealthItemsSize = 0;
        for(int i = 0; i < boughtFuelItemsSize; i++) {
            if(boughtFuelItems[i] != NULL) {
                    delete boughtFuelItems[i];
            }
        }
        delete [] boughtFuelItems;
	    boughtFuelItems = NULL;
	    boughtFuelItemsSize = 0;
        }
    }
}

void timer_start(std::function<void(void)> func, unsigned int interval)
{
    std::thread([func, interval]() {
    while (state != QUIT)
    {
        //for fps calculation
        //chk++;
        //if (chk >= 31){printf("fps %d\n", tst); tst = 0; chk = 0;}
        auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(interval);
        auto y = std::chrono::steady_clock::now();
        func();
        auto z = y - std::chrono::steady_clock::now();
        auto wait = x - z;
        std::this_thread::sleep_until(wait);
    }
	}).detach();
}

bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER |  SDL_INIT_AUDIO) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //creating an outer window
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        DisplayManager::SCREEN_HEIGHT = DM.h;
        DisplayManager::SCREEN_WIDTH = DM.w;
        DisplayManager::GAME_WIDTH = DisplayManager::SCREEN_WIDTH * 3;
        
        gWindow = SDL_CreateWindow( "DEFENDER", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DisplayManager::SCREEN_WIDTH, 				DisplayManager::SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		// Different checks to make sure the necessary components are initialized for the game
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //the renderer on which textures will be updated
			DisplayManager::gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( DisplayManager::gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else{
                //just giving the renderer black colour
                SDL_SetRenderDrawColor( DisplayManager::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
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
                else{
                    DisplayManager::lazy = TTF_OpenFont("../resources/lazy.ttf", 45);
                    if( DisplayManager::lazy == NULL )
                    {
                        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
                    }
                }
                //Initialize SDL_mixer
                //the 2048 is the size of the audios that we will be playing so we can increase this
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
                //creating semaphore to only allow 1 thread to access data at a time.
                dataLock = SDL_CreateSemaphore(1);
            }
        }
    }
    if (success){
        //Load music
        menuMusic = Mix_LoadMUS( "../resources/Sounds/menuMusic.ogg" );
        if( menuMusic == NULL )
        {
            printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }
        gameMusic = Mix_LoadMUS( "../resources/Sounds/gameMusic.ogg" );
        if( gameMusic == NULL )
        {
            printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }
    }
    return success;
}

void close()
{
	// Delete all the created instances after the game ends
    delete clickLocation;
    delete menuFrame;
    delete myFrame;
    delete shopFrame;
    myFrame = NULL;
    menuFrame = NULL;
    shopFrame = NULL;
    clickLocation = NULL;
    //Free semaphore
    SDL_DestroySemaphore( dataLock );
    dataLock = NULL;

    TTF_CloseFont(DisplayManager::lazy);
    DisplayManager::lazy = NULL;

	// SDL_DestroyRenderer( DisplayManager::gRenderer);
    // DisplayManager::gRenderer = NULL;

    //Free the music
    Mix_FreeMusic( menuMusic );
    menuMusic = NULL;
    Mix_FreeMusic( gameMusic );
    gameMusic = NULL;
    
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    TTF_Quit();
	IMG_Quit();
    SDL_Quit();
}
