#ifndef EXEC_H
#define EXEC_H
#include "Em_alg.h"
#include "Wave_alg.h"
#include "Dbscan_alg.h"
#include "Kmeans_alg.h"
#include "factors.h"
#include "span_tree.h"

using namespace std;

class Exec
{
    public:
        Exec(){}
        Em_alg em;
        Kmeans_alg kmeans;
        Wave_alg wave;
        Dbscan_alg dbscan;
        Factor factors;
        Span_tree spanning_tree;
        ~Exec(){}
};

#endif