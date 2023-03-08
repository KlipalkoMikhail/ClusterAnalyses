#ifndef STORAGE_H
#define STORAGE_H
#include "headers.h"
#include "cluster.h"

using namespace std;

class Storage
{
    public:
        Storage();
        vector <Cluster> clusters;
        void resize(int n);
        ~Storage();
};

#endif