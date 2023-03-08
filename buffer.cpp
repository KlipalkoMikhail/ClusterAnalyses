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
    for (int i = 0; i < cld.size(); i++)
    {
        double prevx = cld.getx_p(i);
        cld.set_x_in_p(prevx + stepx, i);
        double prevy = cld.gety_p(i);
        cld.set_y_in_p(prevy + stepy, i);
        cld.center.setx(cld.center.getx() + stepx);
        cld.center.sety(cld.center.gety() + stepy);
    }
}

void Buffer::rotate(Cloud &cld, double degrees)
{
    double a = degrees;

    for (int i = 0 ; i < cld.size(); i++)
    {
        double prevx = cld.getx_p(i) - cld.center.getx();
        double prevy = cld.gety_p(i) - cld.center.gety();
        cld.set_x_in_p(prevx*cos(a) - prevy*sin(a) + cld.center.getx(), i);
        cld.set_y_in_p(prevx*sin(a) + prevy*cos(a) + cld.center.gety(), i);
        //cout << "Previous is ";
        //cout << prevx << " " << prevy << endl;
        //cout << "New is ";
        //cout << prevx*cos(a) - prevy*sin(a) << " " << prevx*sin(a) + prevy*cos(a) << endl;
    }
}

void Buffer::copy(Cloud & cld)
{
    cloud = cld;
}

void Buffer::print()
{
    for (size_t i = 0; i < (size_t)cloud.size(); i++)
    {
        cout << cloud.getx_p(i) << '\t';
        cout << cloud.gety_p(i) << endl;
    }
}

void Buffer::past(Field & field)
{
    field.add_cloud(cloud);
}
