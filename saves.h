#ifndef SAVES_H
#define SAVES_H
#include "cluster.h"
#include "Find_Cluster.h"
class Saves
{
    private:
        vector <FindCluster> findClusters;
        int size;
        vector <int> codes;
        FindCluster FindClusterPtr;
    public:
        Saves();
        vector <Cluster> & get_clusters(int k);
        void getcode(int k);
        void save(vector <Cluster> cl, int ind);
        void cluster_save(int m, int N, vector <Point> &points);
        int ncluster();
        int get_k_code(int k);
        ~Saves();
};

#endif
 