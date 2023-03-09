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
        vector <FindCluster> & getFindClusters();
        FindCluster & getFindCluster(int index);
        void saveFindCluster(vector <Cluster> clusters, int k, double r, int FieldID, string name);
        vector <Cluster> & get_clusters(int k);
        void saveResult(FindCluster &findCluster, Field &field);
        int ncluster();
        ~Saves();
};

#endif
 