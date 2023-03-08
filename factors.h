#ifndef FACTORS_H
#define FACTORS_H

#include "headers.h"
#include <bits/stdc++.h>
#include "point.h"
using namespace std;

class Factor
{
    public:
        Factor(){}
        vector <double> calculate_factors(vector <Point> arr);
        ~Factor(){}
};

#endif