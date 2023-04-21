#include "buffer.h"
#include "headers.h"
#include "field.h"
#include "point.h"
#define REP(i, a, b) for (size_t i = a; i < (size_t)b; i++)
#include <cmath>

Buffer::Buffer()
{
    state = 0;
}

Buffer::~Buffer(){}

void Buffer::shift(Cloud &cld, double stepx, double stepy)
{
    for (int i = 0; i < cld.getSize(); i++)
    {
        double prevx = cld.getXofPoint(i);
        cld.setXinPointByID(prevx + stepx, i);
        double prevy = cld.getYofPoint(i);
        cld.setYinPointByID(prevy + stepy, i);
        cld.center.setx(cld.center.getx() + stepx);
        cld.center.sety(cld.center.gety() + stepy);
    }
}

void Buffer::rotate(Cloud &cld, double degrees)
{
    double a = degrees;

    for (int i = 0 ; i < cld.getSize(); i++)
    {
        double prevx = cld.getXofPoint(i) - cld.center.getx();
        double prevy = cld.getYofPoint(i) - cld.center.gety();
        cld.setXinPointByID(prevx*cos(a) - prevy*sin(a) + cld.center.getx(), i);
        cld.setYinPointByID(prevx*sin(a) + prevy*cos(a) + cld.center.gety(), i);
    }
}

void Buffer::copy(Cloud & cld)
{
    cloud = cld;
}

void Buffer::print()
{
    for (size_t i = 0; i < (size_t)cloud.getSize(); i++)
    {
        cout << cloud.getXofPoint(i) << '\t';
        cout << cloud.getYofPoint(i) << endl;
    }
}

void Buffer::past(Field & field)
{
    field.addCloud(cloud);
}
