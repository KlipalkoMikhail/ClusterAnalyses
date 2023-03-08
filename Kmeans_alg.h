#ifndef KMEANS_ALG_H
#define KMEANS_ALG_H

#include "field.h"
#include "cluster.h"

using namespace std;

class Kmeans_alg
{
    public:
        Kmeans_alg(){}
        vector <Cluster> k_means(int k, Field &field);
        ~Kmeans_alg(){}
};

#endif