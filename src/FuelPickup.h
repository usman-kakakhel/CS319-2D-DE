#ifndef __FUELPICKUP_H
#define __FUELPICKUP_H

#include "Pickup.h"

class FuelPickup : public Pickup{
private:
    static FuelPickup* instance;
    FuelPickup(Point newPos, int newAmount);

    //for renderer
    string sprite = "../resources/fuel.png";
    DisplayManager::CustomTexture* mCTexture = NULL;

public:
    static FuelPickup* getInstance(Point newPos, int newAmount);
    static void deleteInstance();
    ~FuelPickup() override;
    int getWidth() override;
    int getHeight() override;
    void render(Point cameraPoint) override;
};

#endif
