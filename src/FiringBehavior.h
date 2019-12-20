#ifndef __FIRING_BEHAVIOR_H
#define __FIRING_BEHAVIOR_H

#include "Point.h"
#include "TargetedWeapon.h"
#define PI 3.14159265

class FiringBehavior {
   public:
      virtual void fire(TargetedWeapon** &weaponList, int &size, Point spaceShipPos, Point myPoint, int newOrientation);
      void operator= (FiringBehavior const &firingBehavior);
};

#endif
