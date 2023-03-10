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
        std::vector <Cluster> findedClusters;
        int size;
        int Knumber;
        double Rnumber;
        std::string name; 
    public:
        int getID();
        int getFieldID();
        int getSize();
        int getKnumber();
        vector <Cluster> &getFindedClusters();
        double getRnumber();
        std::string getName();
        void setID(int id);
        void setFieldID(int id);
        void setSize(int sz);
        void setKnumber(int k);
        void setRnumber(double r);
        void setName(std::string nm);
        void printParameters();
};

#endif