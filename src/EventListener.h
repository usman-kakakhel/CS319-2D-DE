#ifndef __EVENTLISTENER_H
#define __EVENTLISTENER_H

#include <SDL2/SDL.h>
#include <string>

#include "MyEnums.h"
#include "Point.h"

class EventListener{
    public:
        EventListener();
        ~EventListener();
        void getEvent(SDL_Event e, bool* keyList, GameState* state, Point* &clickLocation);
        
    private:
        
        
};

#endif