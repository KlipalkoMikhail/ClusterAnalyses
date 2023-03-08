#include "Wave_alg.h"
#include "point.h"
#include "headers.h"
#include <list>
#include "cluster.h"

using namespace std;

vector <Cluster> Wave_alg::wave(double mode, Field &field)
{
    vector <Point> points = field.p();
    char filename[120];
    ofstream gnufile;
    // ������� ��������, ������� ����������, ������� �����, ������� a, b, nul, ���������� N - ����� �����, T - ������
    vector <Cluster> clusters;

    int N = field.size();

    vector <vector <double>> D;
    vector <vector <int>> B;

    vector <int> a(N);
    vector <int> b(N);
    vector <int> nul(N);

    int T = 1;

    // �������� ������
    D.resize(N);
    B.resize(N);

    // �������� ������
    for (int i = 0; i < N; i++)
    {
        D[i].resize(N);
        B[i].resize(N);
    }

    // ������� ������� ����������
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            D[i][j] = distance(field.p(i), field.p(j));
        }
    }

    // ������� ������� �����
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if(D[i][j] < mode)
                B[i][j] = 1;
            else B[i][j] = 0;
        }
    }

    // ����������� ������
    D.clear();

    // ������� �����: index - �����, �������� � ������ T, indexnew - ��� ������ ���� �������� �����
    list <int> index;
    list <int> indexnew;
    // ������� �������: temp - ������ ��� ������ ��������, blong - ������ �������� � �� �������� �����
    vector <int> temp(N);
    vector <int> blong(N);

    // �������� �����
    int i = 0;
    for (int k = 0; k < N; k++)
    {
        if (!blong[k])
        {
            // ������� ������� � ��������� � ���� �����
            Cluster cl;
            cl.reserve(N);
            blong[k] = 1;
            a[k] = 1;
            cl.add_p(k);
            // ������� ����, �������� ����� ���������� �����
            b = a;
            index.push_back(k);

            // �������� �� ����� ��������� �����
            while(1)
            {
                for(list <int> :: iterator it = index.begin(); it != index.end(); it++)
                {
                    for(int i = 0 ; i < N; i++)
                    {
                        // ��������� ��������� �� ����� ������ � ���������� �� ���
                        if(((B[*it][i]) == 1) && (a[i] == 0) && (blong[i] == 0))
                        {
                            // �������� �����
                            b[i] = T + 1;
                            // ��������� � �������
                            cl.add_p(i);
                            // �������, ��� �� ��� ��� ������
                            blong[i] = 1;
                            // ���������� ����� � ���������� ����� (��� ��������� ������)
                            indexnew.push_back(i);
                        }
                    }
                }

                // ����� ����� ������� ���������� ����������� � ������ index
                index.clear();
                index.merge(indexnew);
                indexnew.clear();
                sprintf(filename, "gnu_%d.dat", i);
                i++;
                gnufile.open(filename);
                for(list <int> :: iterator it = index.begin(); it != index.end(); it++)
                {
                    gnufile << points[*it].getx() << "\t" << points[*it].gety() << endl;
                }
                gnufile.close();
                if (a == b) break;
                temp = a;
                a = b;
                T = T + 1;
            }
            clusters.push_back(cl);
        }
        // ��������� ��������� T, a, b
        T = 1;
        a = b = nul;
    }
    // ��������� ���������
    cout << "The wave algorithm has done its work\n";
    return clusters;
}