#ifndef WAVE_ALG_H
#define WAVE_ALG_H

#include "field.h"
#include "cluster.h"

using namespace std;

class Wave_alg
{
    public:
        Wave_alg(){}
        vector <Cluster> wave(double mode, Field &field); 
        ~Wave_alg(){}
};

#endif