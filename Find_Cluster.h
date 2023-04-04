#ifndef FIND_CLUSTER_H
#define FIND_CLUSTER_H
#include <iostream>
#include <string>
#include <vector>
#include "cluster.h"

class FindCluster
{
    private:
        int ID;
        int FieldID;
        int DBFID;
        int size;
        int Knumber;
        int state;
        double Rnumber;
        std::vector <Cluster> findedClusters;
        std::string name; 
    public:
        FindCluster();
        int getID();
        int getFieldID();
        int getSize();
        int getKnumber();
        int getDBFID();
        int getState();
        double getRnumber();
        void setID(int id);
        void setFieldID(int id);
        void setState(int state);
        void setSize(int sz);
        void setKnumber(int k);
        void setRnumber(double r);
        void setName(std::string nm);
        void setDBFID(int dbfid);
        void printParameters();
        vector <Cluster> &getFindedClusters();
        std::string getName();
        
};

#endif