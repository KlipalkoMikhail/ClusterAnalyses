#include "headers.h"
void printcl(Cluster cl, Field &field);

double scalx(std::vector <Point> &x, std::vector <short int> &bl, int N)
{
    double scall = 0;

    for(int i = 0; i < N; i++)
    {
        scall += (x[i]).getx()*bl[i];
        x[i].getx();
    }

    return scall;
}

double scaly(std::vector <Point> &x, std::vector <short int> &bl, int N)
{
    double scall = 0;

    for(int i = 0; i < N; i++)
    {
        scall += (x[i]).gety()*bl[i];
    }

    return scall;
}

void printvec(vector <int> a)
{
    for (int i = 0; i < (int)a.size(); i++)
        cout << a[i] << " ";
    cout << endl;
}

bool iscore(vector <vector<int>> &B, int k, int m)
{
    int l = 0;
    for (int i = 0; i < (int)B[k].size(); i++)
    {
        if (B[k][i] == 1) l++;
    }

    if (l >= m) return 1;
    else return 0;

}

void printcl(Cluster cl, Field &field)
{
    int N = field.size();
    std::ofstream fout;
    std::ofstream foutother;
    vector <Point> points = field.p();
    char filename[120];
    sprintf(filename, "%d.dat", 0);
    fout.open(filename);
    sprintf(filename, "%d.dat", 1);
    for (int j = 0; j < N; j++)
    {
        if (cl.tr(j))
            fout << points[j].getx() << "\t\t" << points[j].gety() << endl;
    }
    foutother.open(filename);
    for (int j = 0; j < N; j++)
    {
        if (!cl.tr(j))
            foutother << points[j].getx() << "\t\t" << points[j].gety() << endl;
    }
    fout.close();
    foutother.close();
}
