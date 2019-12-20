#ifndef __FIRE_RED_BOLT_H
#define __FIRE_RED_BOLT_H

#include "FiringBehavior.h"
#include "FireRedBolt.h"
#include "RedBolt.h"

class FireRedBolt : public FiringBehavior {
	public:
		void fire(TargetedWeapon** &weaponList, int &size, Point spaceShipPos, Point newPos, int newOrientation) override;
};

#endif
