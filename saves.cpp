#include "headers.h"
#include "saves.h"

// �����, ����������� �������� � ����, ������� ���������: m - ���������� ����� ���������, N - ����� ����� � ����, &points - ������ �� �����
void Saves::cluster_save(int m, int N, vector <Point> &points)
{
    // ������� ������� ������ ���������
    int k = clust[m].size();
    cout << k << endl;
    vector <Cluster> clusters = clust[m];

    // ����� ��� ���
    std::ofstream fout[1000];

    // �������� �������� � �����
    for (int i = 0; i < k; i++)
    {
        char filename[120];
        sprintf(filename, "o_%d_%d.dat", m, i + 1);
        fout[i].open(filename);
        for (int j = 0; j < N; j++)
        {
            if (clusters[i].tr(j) == 1)
                fout[i] << points[j].getx() << "\t\t" << points[j].gety() << endl;
        }
        fout[i].close();
    }
    char filename[120];
    sprintf(filename, "gnu_%d.dat", m);
    ofstream gnufile;
    gnufile.open(filename);
    gnufile << "set term png" << endl << "set output \"res_" << m << ".png\"" << endl;
    gnufile << "plot [-20:20][-20:20]\\" << endl;
    gnufile << "for [i = 1:" << k << "] \"o_" << m << "_\".i.\".dat\"\\" << endl;
    gnufile << "w p lt 7 lc i + 1 lw 1" << endl;
    gnufile << "unset output" << endl;
    //gnufile << "set term win" << endl;
    gnufile.close();
}
 
int Saves::ncluster()
{
    return (int)clust.size();
}
// ����������� Saves
Saves::Saves()
{
    clust.resize(1000);
    codes.resize(1000);
    k = 0;
}

// ��������� �������, ������� ��������� &cl - ��������, ind - ��� ���������
void Saves::save(vector <Cluster> cl, int ind)
{
    clust[k] = cl;
    codes[k] = ind;
    k++;
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

vector <Cluster> & Saves::get_clusters(int k)
{
    return clust[k];
}
