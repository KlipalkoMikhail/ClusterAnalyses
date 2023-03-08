#ifndef DBSCAN_ALG_H
#define DBSCAN_ALG_H
using namespace std;
#include "field.h"
#include "cluster.h"

class Dbscan_alg
{
    public:
        Dbscan_alg(){}
        vector <Cluster> dbscan(int m, double r, Field &field);
        ~Dbscan_alg(){}
};

#endif