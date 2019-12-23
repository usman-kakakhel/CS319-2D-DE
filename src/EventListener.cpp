/*
Event Listener class
This class implements the event listening for the game
*/
#include "EventListener.h"

// Constructor and Destructor need not to be initialized
EventListener::EventListener(){

}
EventListener::~EventListener(){

}

// Get the event type based on the location of the mouse press or key press
void EventListener::getEvent(SDL_Event e, bool* keyList, GameState* state, Point* &clickLocation){
    while( SDL_PollEvent( &e ) != 0 ){
        //Identify this event
        if( e.type == SDL_QUIT ){
            *state = QUIT;
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
            else if(e.key.keysym.sym == SDLK_ESCAPE)
            {
                if (*state == RESUME)
                    *state = PAUSE;
                if (*state == GAME_OVER)
                    *state = MAIN_MENU;
                return;
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

		//get mouse evevnts
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT){
            clickLocation = new Point(e.button.x, e.button.y);
            return;
        }
        else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT){
            if (clickLocation != NULL){
                delete clickLocation;
                clickLocation = NULL;
                return;
            }
        }            
    }
}
