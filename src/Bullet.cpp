#include "Bullet.h"

Bullet::Bullet(Point newPos, int newSpeed, int newDamage, int newOrientation):TargetedWeapon(newPos, newSpeed, newDamage, newOrientation){
}


Bullet::~Bullet(){}


//update position
void Bullet::updatePosition(){
	int x = this->position.getX();
	int y = this->position.getY();
	x = cos((orientation - 90)*(PI/180))*speed + x; //x= speed*cos(theta) + x
	y = sin((orientation - 90)*(PI/180))*speed + y;
	Point p(x,y);
	this->setPosition(p);
}
