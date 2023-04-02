#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <vector>
#include "point.h"
#include "cloud.h"
#include "field.h"
#include "cluster.h"
#include <random>
#include <string>
#include "MyException.h"
#pragma once

#define STRICT_MODE_OFF                                                                 \
    _Pragma("GCC diagnostic push")                                            \
    _Pragma("GCC diagnostic ignored \"-Wreturn-type\"")             \
    _Pragma("GCC diagnostic ignored \"-Wdelete-non-virtual-dtor\"") \
    _Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")        \
    _Pragma("GCC diagnostic ignored \"-pedantic\"")                 \
    _Pragma("GCC diagnostic ignored \"-Wshadow\"")                  \
    _Pragma("GCC diagnostic ignored \"-Wold-style-cast\"")          \
    _Pragma("GCC diagnostic ignored \"-Wswitch-default\"")

/* Addition options that can be enabled
    _Pragma("GCC diagnostic ignored \"-Wpedantic\"")                \
    _Pragma("GCC diagnostic ignored \"-Wformat=\"")                 \
    _Pragma("GCC diagnostic ignored \"-Werror\"")                   \
    _Pragma("GCC diagnostic ignored \"-Werror=\"")                  \
    _Pragma("GCC diagnostic ignored \"-Wunused-variable\"")         \
*/

#define STRICT_MODE_ON                                                                  \
    _Pragma("GCC diagnostic pop")


using namespace std;
double scalx(std::vector <Point> &x, std::vector <short int> &bl, int N);
double scaly(std::vector <Point> &x, std::vector <short int> &bl, int N);
void printvec(vector <int> a);
bool iscore(vector <vector<int>> &B, int k, int m);
double distance(const Point &x, const Point &y);




