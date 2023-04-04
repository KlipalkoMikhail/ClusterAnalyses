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
        void printFindCluster(int FCID, int FID);
        void printLaunches();
        void saveFindCluster(vector <Cluster> clusters, Field &field, int k, double r, string name);
        void saveResult(FindCluster &findCluster, Field &field);
        vector <vector <FindCluster>> & getFindClusters();
        vector <Cluster> & get_clusters(int FID, int FCID);
        FindCluster & getFindCluster(int FID, int FCID);
        int getSize();
        void setSize(int sz);
        void resizeFindClusters(int sz);
        ~Saves();
};

#endif
 