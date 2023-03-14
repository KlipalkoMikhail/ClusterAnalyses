#include "headers.h"
#include "saves.h"

void saveDataInFiles(FindCluster &findCluster, Field &field)
{
    vector <Cluster> &findedClusters = findCluster.getFindedClusters();
    vector <Point> &points = field.get_points_reference();
    int ClusterSize = findCluster.getSize();
    int FieldSize = field.size();
    int FCID = findCluster.getID();

    //findCluster.printParameters();
    //cout << ClusterSize << endl;
    ofstream fout;
    string filename;
    for (int i = 0; i < ClusterSize; i++)
    {
        filename = "OutPut_" + to_string(FCID) + "_" + to_string(i + 1) + ".txt";
        fout.open(filename, ios::out | ios::binary);
        for (int j = 0; j < FieldSize; j++)
        {
            if (findedClusters[i].tr(j) == 1)
                fout << showpos << points[j].getx() << "\t\t" << showpos << points[j].gety() << endl;
        }
        fout.close();
    }
}

void printInTextFileGNUPlotCommands(FindCluster &findCluster)
{
    ofstream gnufile;
    int FCID = findCluster.getID();
    int ClusterSize = findCluster.getSize();
    string filename = "GnuFile_" + to_string(FCID) + ".txt";

    gnufile.open(filename, ios::out | ios::binary);
    //gnufile << "set term png" << endl << "set output \"res_" << FCID << ".png\"" << endl;
    gnufile << "plot [-20:20][-20:20]\\" << endl;
    gnufile << "for [i = 1:" << ClusterSize << "] \"OutPut_" << FCID << "_\".i.\".txt\"\\" << endl;
    gnufile << "w p lt 7 lc i + 1 lw 1" << endl;
    //gnufile << "unset output" << endl;
    gnufile.close();
}

void Saves::saveResult(FindCluster &findCluster, Field &field)
{
    saveDataInFiles(findCluster, field);
    printInTextFileGNUPlotCommands(findCluster);
}
 
int Saves::ncluster()
{
    return findClusters.size();
}

Saves::Saves()
{
    findClusters.resize(1000);
    size = 0;
}

void Saves::saveFindCluster(vector <Cluster> clusters, int k, double r, int FieldID, string name)
{
    vector <Cluster> &findedClusters = findClusters[size].getFindedClusters();
    int ClustersSize = clusters.size();
    findedClusters.resize(ClustersSize);
    
    for(int i = 0; i < ClustersSize; i++)
    {
        Cluster cluster = clusters[i];
        cluster.setID(i);
        cluster.setFCID(size);
        findedClusters[i] = cluster;
    }
    
    findClusters[size].setName(name);
    //cout << name << endl;
    findClusters[size].setID(size);
    //cout << size << endl;
    findClusters[size].setFieldID(FieldID);
    //cout << FieldID << endl;
    findClusters[size].setKnumber(k);
    //cout << k << endl;
    findClusters[size].setRnumber(r);
    //cout << r << endl;
    findClusters[size].setSize(ClustersSize);
    //cout << ClustersSize << endl;
    size++;
}

Saves::~Saves(){}

vector <Cluster> & Saves::get_clusters(int FCID)
{
    vector <Cluster> &findedClusters = findClusters[FCID].getFindedClusters();
    return findedClusters;
}

vector <FindCluster> &Saves::getFindClusters()
{
    return findClusters;
}

FindCluster & Saves::getFindCluster(int index)
{
    return findClusters[index];
}
