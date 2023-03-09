#include "headers.h"
#include "saves.h"

void saveDataInFiles(FindCluster &findCluster, Field &field)
{
    const vector <Cluster> &findedClusters = findCluster.getFindedClusters;
    const vector <Point> &points = field.get_points_reference();
    int ClusterSize = findedClusters.size();
    int FieldSize = field.size();
    int FCID = findCluster.getID();

    ofstream fout;
    string filename;
    for (int i = 0; i < ClusterSize; i++)
    {
        filename = "OutPut_" + to_string(FCID) + to_string(i + 1);
        fout.open(filename);
        for (int j = 0; j < FieldSize; j++)
            if (clusters[i].tr(j) == 1)
                fout << showpos << points[j].getx() << "\t\t" << showpos << points[j].gety() << endl;
        fout.close();
    }
}

void printInTextFileGNUPlotCommands(FindCluster &findCluster)
{
    ofstream gnufile;
    int FCID = findCluster.getID();
    int ClusterSize = findedClusters.size();
    string filename = "GnuFile_" + to_string(FCID);

    gnufile.open(filename);
    gnufile << "set term png" << endl << "set output \"res_" << FCID << ".png\"" << endl;
    gnufile << "plot [-20:20][-20:20]\\" << endl;
    gnufile << "for [i = 1:" << ClusterSize << "] \"o_" << FCID << "_\".i.\".dat\"\\" << endl;
    gnufile << "w p lt 7 lc i + 1 lw 1" << endl;
    gnufile << "unset output" << endl;
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
    codes.resize(1000);
    size = 0;
}

void Saves::saveFindCluster(vector <Cluster> clusters, int k, double r, int FieldID, string name)
{
    vector <Cluster> &findedClusters = findClusters[size].getFindedClusters();
    int size = findedClusters.size();
    findClusters[size].setname(name);
    findClusters[size].setID(ID);
    findClusters[size].setFieldID(FID);
    findClusters[size].setKnumber(k);
    findClusters[size].setRnumber(r);
    findClusters[size].setSize(size);
    size++;
}

Saves::~Saves(){}

void Saves::getcode(int k)
{
    if (codes[k] == 1) cout << "It is K means algorithm\n" << "It was done as " << k << "th algorithm\n";
    if (codes[k] == 2) cout << "It is Wave algorithm\n" << "It was done as " << k << "th algorithm\n";
    if (codes[k] == 3) cout << "It is DBscan algorithm\n" << "It was done as " << k << "th algorithm\n";
    if (codes[k] == 4) cout << "It is EXPMAX algorithm\n" << "It was done as " << k << "th algorithm\n";
    if (codes[k] == 5) cout << "It is SPANTREE algorithm\n" << "It was done as " << k << "th algorithm\n";
}

int Saves::get_k_code(int k)
{
    return codes[k];
}

vector <Cluster> & Saves::get_clusters(int FCID)
{
    findedClusters = findClusters[FCID].getFindedClusters();
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
