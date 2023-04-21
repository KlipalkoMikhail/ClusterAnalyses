#include "point.h"

Point::Point()
{
    x = 0;
    y = 0;
    NP = 0;
    colour = 0;
}

Point::Point(double x1, double x2)
{
    this -> x = x1;
    this -> y = x2;
}

Point::Point(const Point& point)
{
    x = point.getx();
    y = point.gety();
    NP = point.getNP();
    colour = point.getColour();
}

Point::~Point(){}

const Point & Point::operator=(const Point & point)
{
    x = point.getx();
    y = point.gety();
    NP = point.getNP();
    colour = point.getColour();
    return *this;
}

void Point::setx(double x1)
{
    x = x1;
}
void Point::sety(double x2)
{
    y = x2;
}
void Point::setnp(int np)
{
    NP = np;
}
void Point::setc(int c)
{
    colour = c;
}
double Point::getx() const
{
    return x;
}
double Point::gety() const
{
    return y;
}
int Point::getNP() const
{
    return NP;
}
int Point::getColour() const
{
    return colour;
}