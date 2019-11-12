#include "EventListener.h"


EventListener::EventListener(){

}

EventListener::~EventListener(){

}

void EventListener::getEvent(SDL_Event e, bool* keyList, bool* quit){
    while( SDL_PollEvent( &e ) != 0 ){
        //Identify this event
        if( e.type == SDL_QUIT ){
            *quit = true;
            return;
        }
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0){
            if (e.key.keysym.sym == SDLK_UP)
            {
                keyList[UP_PRESSED] = true;
                return ;
            }
            else if (e.key.keysym.sym == SDLK_DOWN)
            {
                keyList[DOWN_PRESSED] = true;
                return ;
            }
            else if (e.key.keysym.sym == SDLK_LEFT)
            {
                keyList[LEFT_PRESSED] = true;
                return ;
            }
            else if (e.key.keysym.sym == SDLK_RIGHT)
            {
                keyList[RIGHT_PRESSED] = true;
                return ;
            }
            else if(e.key.keysym.sym == SDLK_z)
            {
                keyList[BULLET_KEY] = true;
                return ;
            }
            else if(e.key.keysym.sym == SDLK_x)
            {
                keyList[MISSILE_KEY] = true;
                return ;
            }
            else if(e.key.keysym.sym == SDLK_c)
            {
                keyList[DESTRUCTION_KEY] = true;
                return ;
            }
            else{return;}
                
        }
        else if( e.type == SDL_KEYUP && e.key.repeat == 0){
            if (e.key.keysym.sym == SDLK_UP)
            {
                keyList[UP_PRESSED] = false;
                return ;
            }
            else if (e.key.keysym.sym == SDLK_DOWN)
            {
                keyList[DOWN_PRESSED] = false;
                return ;
            }
            else if (e.key.keysym.sym == SDLK_LEFT)
            {
                keyList[LEFT_PRESSED] = false;
                return ;
            }
            else if (e.key.keysym.sym == SDLK_RIGHT)
            {
                keyList[RIGHT_PRESSED] = false;
                return ;
            }
            else if(e.key.keysym.sym == SDLK_z)
            {
                keyList[BULLET_KEY] = false;
                return ;
            }
            else if(e.key.keysym.sym == SDLK_x)
            {
                keyList[MISSILE_KEY] = false;
                return ;
            }
            else if(e.key.keysym.sym == SDLK_c)
            {
                keyList[DESTRUCTION_KEY] = false;
                return ;
            }
            else{return;}
                
        }
                 
    }

}