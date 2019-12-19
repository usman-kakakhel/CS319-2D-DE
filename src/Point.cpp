#include "Point.h"

Point::Point(int x, int y){
    Point::x = x;
    Point::y = y;
}

Point::~Point(){

}

int Point::getX() const{
    return x;
}

void Point::setX(int x){
    Point::x = x;
}

int Point::getY() const{
    return y;
}

void Point::setY(int y){
    Point::y = y;
}


Point Point::operator= (Point const &thePoint){
    Point::setX(thePoint.getX());
    Point::setY(thePoint.getY());
}