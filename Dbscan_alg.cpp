#include "headers.h"
#include "field.h"
#include "cluster.h"
#include "point.h"
#include <list>
#include "Dbscan_alg.h"

vector <Cluster> Dbscan_alg::dbscan(int m, double r, Field &field)
{
    // ������� ��������, ������� ����������, ������� �����, ������� a, b, nul, ���������� N - ����� �����, T - ������
    vector <Cluster> clusters;

    int N = field.getSize();

    vector <vector <double>> D;
    vector <vector <int>> B;

    vector <int> a(N);
    vector <int> b(N);
    vector <int> nul(N);

    int T = 1;

    // �������� ������
    D.resize(N);
    B.resize(N);
    double step = 0;

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
            D[i][j] = distance(field.getPoint(i), field.getPoint(j));
            //step += D[i][j]/2;
        }
    }

    // ������� �����
    //step = step/(2*N*(N - 1));
    step = r;
    // ������� ������� �����
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if(D[i][j] < step)
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
    for (int k = 0; k < N; k++)
    {
        a = nul;
        b = nul;
        if (!blong[k])
        {
            // ������� ������� � ��������� � ���� �����, ���� ��� �� ����, �� ����������
            if (!iscore(B, k, m)) continue;
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
                    // ���������, �������� �� ����� �����, ���� ��, �� � ������ ������ ��������� �� �������
                    if(!iscore(B, *it, m)) continue;

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

                if (a == b) break;
                temp = a;
                a = b;
                T = T + 1;
            }
            clusters.push_back(cl);
        }
        // ��������� ��������� T, a, b
        T = 1;
    }
    // ������� ������� ��� �����, �� �������� � ������ ��������
    Cluster cl;
    cl.reserve(N);

    vector <Point> points = field.getPoints();
    for (int i = 0; i < N; i++)
    {
        if (!blong[i])
            cl.add_p(i);
    }
    clusters.push_back(cl);
    // ������� ���������� � ��������� ������ ���������
    Cluster cl_periff;
    cl_periff.reserve(N);
    // ���������� � �������
    for (int i = 0; i < N; i++)
    {
        if (blong[i] && !iscore(B, i, m))
            cl_periff.add_p(i);
        blong[i] = 0;
    }

    clusters.push_back(cl_periff);

    cout << "DBscan has perfectly done" << endl;
    return clusters;
}