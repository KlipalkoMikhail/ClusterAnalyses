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

vector <Cluster> & FindCluster::getFindedClusters()
{
    return findedClusters;
}


void FindCluster::setDBFID(int dbfid)
{
    DBFID = dbfid;
}

int FindCluster::getDBFID()
{
    return DBFID;
}

void FindCluster::printParameters()
{
    cout << "findCluster: ";
    cout     << "ID " << ID;
    cout     << " FieldID " << FieldID
         << " DBFID " << DBFID
         << " Name " << name
         << " Size " << size
         << " K " << Knumber
         << " R " << Rnumber << endl;
}

FindCluster::FindCluster()
{
    state = 0;
    size = 0;
}

void FindCluster::setState(int st)
{  
    this -> state = st;
}

int FindCluster::getState()
{
    return state;
}