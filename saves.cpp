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
    cout << ClusterSize << endl;

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
    cout << "eg" << endl;
    printInTextFileGNUPlotCommands(findCluster);
}
 
int Saves::ncluster()
{
    return findClusters.size();
}

Saves::Saves()
{
    size = 0;
}

void Saves::printFindCluster(int FID, int FCID)
{
    FindCluster findCluster = getFindCluster(FID, FCID);
    int ID, fID, SIZE, K;
    double R;
    string name;
    ID = findCluster.getID();
    fID = findCluster.getFieldID();
    SIZE = findCluster.getSize();
    K = findCluster.getKnumber();
    R = findCluster.getRnumber();
    name = findCluster.getName();
    vector <Cluster> & clusters = findCluster.getFindedClusters();
    cout << ID << ' ' << fID << ' ' << SIZE << ' ' << K << ' ' << R << ' ' << name << endl;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < clusters[i].getFieldSize(); j++)
        {
            cout << clusters[i].tr(j) << ' ';
        }
        cout << endl;
    }
}

void Saves::saveFindCluster(vector <Cluster> clusters, Field &field, int k, double r, string name)
{
    int FID = field.getID();
    int DBFID = field.getDBID();
    int FCID = field.getNFC();

    if (FID == size)
    {
        size++;
        findClusters.resize(size);
    }
    else if (FID > size) throw MyException("Wrong FID in saving find clusters");

    findClusters[FID].resize(findClusters[FID].size() + 1);

    vector <Cluster> &findedClusters = findClusters[FID][FCID].getFindedClusters();
    int ClustersSize = clusters.size();
    findedClusters.resize(ClustersSize);

    for(int i = 0; i < ClustersSize; i++)
    {
        Cluster cluster = clusters[i];
        cluster.setID(i);
        cluster.setFCID(FCID);
        findedClusters[i] = cluster;
    }
    
    findClusters[FID][FCID].setName(name);
    //cout << name << endl;
    findClusters[FID][FCID].setID(FCID);
    findClusters[FID][FCID].setDBFID(DBFID);
    //cout << size << endl;
    findClusters[FID][FCID].setFieldID(FID);
    //cout << FieldID << endl;
    findClusters[FID][FCID].setKnumber(k);
    //cout << k << endl;
    findClusters[FID][FCID].setRnumber(r);
    //cout << r << endl;
    findClusters[FID][FCID].setSize(ClustersSize);
    //cout << ClustersSize << endl;
    field.setNFC(field.getNFC() + 1);
}

Saves::~Saves()
{
    vector <vector <FindCluster>> ().swap(findClusters);
}

vector <Cluster> & Saves::get_clusters(int FID, int FCID)
{
    vector <Cluster> &findedClusters = findClusters[FID][FCID].getFindedClusters();
    return findedClusters;
}

vector <vector <FindCluster>> &Saves::getFindClusters()
{
    return findClusters;
}

FindCluster & Saves::getFindCluster(int FID, int FCID)
{
    return findClusters[FID][FCID];
}

void Saves::setSize(int sz)
{
    size = sz;
}

int Saves::getSize()
{
    return size;
}

void Saves::resizeFindClusters(int sz)
{
    if (size < sz)
    {
        findClusters.resize(sz);
        size = sz;
        findClusters[sz - 1].resize(findClusters[sz - 1].size() + 1);
    }
    else 
        findClusters[sz - 1].resize(findClusters[sz - 1].size() + 1);
}
