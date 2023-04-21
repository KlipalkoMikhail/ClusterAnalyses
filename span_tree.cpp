#include "headers.h"
#include "cluster.h"
#include <cfloat>
#include "point.h"
#include <list>
#include "span_tree.h"

using namespace std;

void Span_tree::span_the_tree(Field & field)
{
    vector <Cluster> clusters;
    vector <Point> pt = field.getPoints();

    int N = field.getSize();

    vector <short int> bl(N);

    vector <vector <short int>> B(N);
    vector <vector <double>> D;

    // �������� ������
    D.resize(N);
    bl.resize(N);

    // �������� ������
    for (int i = 0; i < N; i++)
    {
        D[i].resize(N);
        B[i].resize(N);
    }

    // ������� ������� ����������
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            D[i][j] = distance(field.getPoint(i), field.getPoint(j));

    double min = DBL_MAX;
    int x = 0;
    int y = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (D[i][j] < min)
            {
                min = D[i][j];
                x = i;
                y = j;
            }
        }
    }

    bl[x] = bl[y] = 1;
    B[x][y] = 1;
    D[x][y] = -1;

    list <int> tree;
    tree.push_back(x);
    tree.push_back(y);

    while (true)
    {
        for (list <int> :: iterator it = tree.begin(); it != tree.end(); it++)
        {
            for (int j = 0; j < N; j++)
            {
                if ((D[*it][j] > 0) && (D[*it][j] < min) && !(bl[j] && bl[*it]))
                {
                    min = D[*it][j];
                    x = *it;
                    y = j;

                }
            }
        }

        if (min == DBL_MAX) break;
        tree.push_back(x);
        tree.push_back(y);
        bl[x] = 1;
        bl[y] = 1;
        B[x][y] = 1;
        D[x][y] = -1;
        min = DBL_MAX;
    }

    ofstream fout("out.dat");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (B[i][j])
            {
                fout << pt[i].getx() << "\t\t" << pt[i].gety();
                fout << endl;
                fout << pt[j].getx() << "\t\t" << pt[j].gety();
                fout << endl;
                fout << endl;
            }
        }
    }
    fout.close();

    ofstream fedge("edges.dat");
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            if (B[i][j])
                fedge << distance(field.getPoint(i), field.getPoint(j)) << endl;
    fedge.close();
    cout << "Success" << endl;

}