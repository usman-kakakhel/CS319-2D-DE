#ifndef __CAMERA_H
#define __CAMERA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "DisplayManager.h"
#include "Point.h"

class Camera : public DisplayManager{
    public:
        Camera();
        ~Camera();
        
        Point getPoint();
        void setPoint(Point myPoint);
        void render(SDL_Renderer* gRenderer);

        void updateCameraPosition(Point shipInitialPoint, Point shipFinalPoint);
        
    private:
        Point myPoint;
        Point backgroundPosStart;
        int trick;
};


#endif