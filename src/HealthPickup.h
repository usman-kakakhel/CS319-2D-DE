#ifndef __HEALTHPICKUP_H
#define __HEALTHPICKUP_H

#include "Pickup.h"

class HealthPickup : public Pickup{
private:
        static HealthPickup* instance;
        HealthPickup(Point newPos, int newAmount);

        //for renderer
        string sprite = "../resources/health.png";
        DisplayManager::CustomTexture* mCTexture = NULL;

public:
        static HealthPickup* getInstance(Point newPos, int newAmount);
        static void deleteInstance();
        ~HealthPickup() override;
	int getWidth() override;
	int getHeight() override;
        void render(Point cameraPoint) override;
};

#endif
