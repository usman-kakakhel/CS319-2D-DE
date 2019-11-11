#ifndef __POINT_H
#define __POINT_H



class Point{
    public:
        Point(int x = 0, int y = 0);
        ~Point();
        int getX() const;
        void setX(int x);
        int getY()const;
        void setY(int y);


        Point operator= (Point const &myPoint);
        
       
    private:
        int x;
        int y;
};

#endif