#include "ClearScreen.h"

//constructor
ClearScreen::ClearScreen(int damageValue, int radiusValue){
        damage = damageValue;
        blastRadius = radiusValue;
}

//destructor
ClearScreen::~ClearScreen(){
        damage = 0;
        blastRadius = 0;
}

