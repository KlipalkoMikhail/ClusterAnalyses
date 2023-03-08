#include "headers.h"
#include "field.h"
#include "cluster.h"
#include "Kmeans_alg.h"

using namespace std;

vector <Cluster> Kmeans_alg::k_means(int k, Field &field)
{
    vector <Point> points = field.p();
    int N = field.size();
    vector <vector <short int>> vec(k);
    vector <Cluster> clusters(k);

    for (int i = 0; i < k; i++)
    {
        // ������� ������ �� N ���������
        vec[i].resize(N);
        // ������� ������ � �������� �� N ���������
        clusters[i].reserve(N);
        // ��������� �����
        clusters[i].add_p(i);
        // ������� �����
        clusters[i].ccenter(points, N);
    }

    while(1)
    {
        // ������������� ������ � 0

        bool flag = 0;
        for (int i = 0; i < N; i++)
        {
            // ���� ����������� ����������
            int indexmin = 0;
            double min = distance(points[i], *(clusters[0].getcen()));

            // ��������� �������� ���������
            vec[0] = clusters[0].p();

            for (int j = 1; j < k; j++)
            {
                // ��������� �����
                vec[j] = clusters[j].p();
                if (min > distance(points[i], *(clusters[j].getcen())))
                {
                    min = distance(points[i], *(clusters[j].getcen()));
                    indexmin = j;
                }
            }

            // ������� �����, ������� � ������� �� ��������
            for (int j = 0; j < k; j++)
            {
                clusters[j].rem_p(i);
            }

            // ��������� ������ � ��� �������, �������� ��� ����� �����������
            clusters[indexmin].add_p(i);

            // ���� ��������� ����, �� ��������� ������ � 1
            for (int m = 0; m < k; m++)
                if (vec[m] != clusters[m].p()) flag = 1;
        }
        // ������������� ������
        for (int i = 0; i < k; i++)
            clusters[i].ccenter(points, N);

        // ��������� ������
        if (flag == 0) break;
    }
    cout << "K means algorithm has perfectly done" << endl;

    // ��������� ���������
    return clusters;
}