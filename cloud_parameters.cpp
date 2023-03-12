#include "headers.h"
#include "cloud_parameters.h"

void CloudParameters::load_index(istream &stream)
{
    int i = 0;
    stream >> i;

    if (stream.fail())
        stream.clear();
    else 
        field_index = i;
}

void CloudParameters::load_size(istream &stream)
{
    int s = 0;
    stream >> s;

    if (stream.fail())
        stream.clear();
    else 
        size = s;
}

void CloudParameters::load_center(istream &stream)
{
    double x, y;
    stream >> x;

    if (stream.fail())
        stream.clear();
    else 
        center_x = x;

    stream >> y;

    if (stream.fail())
        stream.clear();
    else
        center_y = y;
}

void CloudParameters::load_dispersion(istream &stream)
{
    double gx, gy;
    stream >> gx;

    if (stream.fail())
        stream.clear();
    else
        dispersion_x = gx;

    stream >> gy;

    if (stream.fail())
        stream.clear();
    else 
        dispersion_y = gy;
}

void CloudParameters::print_parameters(ostream &stream)
{
    stream.setf(ios::left);
    stream << size << '\t' << center_x << '\t' << center_y << '\t' << dispersion_x << '\t' << dispersion_y << endl;
}