#ifndef __EVENTLISTENER_H
#define __EVENTLISTENER_H

#include <SDL2/SDL.h>
#include <string>

#include "MyEnums.h"


class EventListener{
    public:
        EventListener();
        ~EventListener();
        void getEvent(SDL_Event e, bool* keyList, bool *quit);
        
    private:
        int a;
        
};

#endif