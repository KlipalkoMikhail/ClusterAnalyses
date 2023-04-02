#ifndef SAVES_H
#define SAVES_H
#include "cluster.h"
#include "Find_Cluster.h"

class Saves
{
    private:
        vector <vector <FindCluster>> findClusters;
        int size;
        FindCluster FindClusterPtr;
    public:
        Saves();
        vector <vector <FindCluster>> & getFindClusters();
        FindCluster & getFindCluster(int FID, int FCID);
        void printFindCluster(int FCID, int FID);
        void saveFindCluster(vector <Cluster> clusters, Field &field, int k, double r, string name);
        vector <Cluster> & get_clusters(int FID, int FCID);
        void saveResult(FindCluster &findCluster, Field &field);
        int ncluster();
        ~Saves();
};

#endif
 