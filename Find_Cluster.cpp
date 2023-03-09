#include "Find_Cluster.h"

int FindCluster::getID()
{
    return ID;
}

int FindCluster::getFieldID()
{
    return FieldID;
}

int FindCluster::getSize()
{
    return size;
}

int FindCluster::getKnumber()
{
    return Knumber;
}

double FindCluster::getRnumber()
{
    return Rnumber;
}

std::string FindCluster::getName()
{
    return name;
}

void FindCluster::setID(int id)
{
    ID = id;
}

void FindCluster::setFieldID(int id)
{
    FieldID = id;
}

void FindCluster::setSize(int sz)
{
    size = sz;
}

void FindCluster::setKnumber(int k)
{
    Knumber = k;
}

void FindCluster::setRnumber(double r)
{
    Rnumber = r;
}

void FindCluster::setName(std::string nm)
{
    name = nm;
}