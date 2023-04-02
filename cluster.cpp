#include "cluster.h"
Cluster::Cluster()
{
    center.setx(0);
    center.sety(0);
    factors.resize(6);
}

void Cluster::setc(int col)
{
    colour = col;
}
void Cluster::reserve(int N)
{
    blong.resize(N);
    for(int i = 0; i < static_cast<int> (blong.size()); i++)
    {
        blong[i] = 0;
    }
}
void Cluster::add_p(int k)
{
    blong[k] = 1;
}

void Cluster::rem_p(int k)
{
    blong[k] = 0;
}

int Cluster::getc()
{
    return colour;
}

Point * Cluster::getcen()
{
    return &center;
}

vector <short int> Cluster::p()
{
    return blong;
}

short int Cluster::tr(int k)
{
    return blong[k];
}

int Cluster::getID()
{
    return ID;
}

int Cluster::getFCID()
{
    return FCID;
}

int Cluster::getSize()
{
    return size;
}

Point Cluster::getCenter()
{
    return center;
}

void Cluster::setID(int id)
{
    ID = id;
}

void Cluster::setFCID(int fcid)
{
    FCID = fcid;
}

void Cluster::setSize(int sz)
{
    size = sz;
}

void Cluster::setCenter(Point cen)
{
    center = cen;
}

int Cluster::getFieldSize()
{
    return blong.size();
}

Cluster::~Cluster(){}
