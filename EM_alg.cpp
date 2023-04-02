#include <bits/stdc++.h>
#include "Em_alg.h"
#include "headers.h"
#include "cluster.h"
#include <cmath>
#include "field.h"
#include "time.h"
#define EPSILON 0.0001
using namespace std;

/*
double EM::cov(vector <double> x, vector <double> y, double ux, double uy)
{
    double sum = 0;
    for (int i = 0; i < (int)x.size(); i++)
    {
        sum += (x[i] - ux)*(y[i] - uy);
    }
    sum = sum/x.size();
    return sum;
}
*/

double Em_alg::norma(const vector <double> & x, const vector <double> &y)
{
    try{
        double sum = 0;
        for (int i = 0; i < (int)x.size(); i++)
        {
            sum += (x[i] - y[i])*(x[i] - y[i]);
        }
            sum = sqrt(sum);
        return sum;
    }
    catch(const char *e_msg){
        cout << e_msg << endl;
        cout << "sth error" << endl;
        return 0;
    }
}

double Em_alg::cov_matrix_xy(const vector <double> &x,const vector <double> &y, const vector <double> &ux, const vector <double> &uy, const vector <double> &a, const double &p, const int &j)
{
    double sum = 0;
    for (int i = 0; i < (int)x.size(); i++)
    {
        sum += a[i]*(x[i] - ux[j])*(y[i] - uy[j]);
    }
    sum /= x.size()*p;
    return sum;
}

double Em_alg::det(const vector <vector <double>> &cov_mat)
{
    return cov_mat[0][0]*cov_mat[1][1] - cov_mat[0][1]*cov_mat[1][0];
}

void Em_alg::printEllipsesForGNU(vector <vector <vector <double>>> &covm, vector <double> &ux, vector <double> &uy, const int &k)
{
    ofstream fout;
    fout.open("fout.dat");
    for (int i = 0 ; i < k; i++)
    {
        double a, b, c, d;
        double detE = det(covm[i]);
        a = covm[i][1][1]/detE;
        b = -covm[i][0][1]/detE;
        c = -covm[i][1][0]/detE;
        d = covm[i][0][0]/detE;

        fout << "f" << i << "(x, y) = " << a << "*(x - " << ux[i] << ")**2 + (" << b << " + " << c << ")*(x - " << ux[i] << ")*(y - " << uy[i] << ") + " << d << "*(y - " << uy[i] << ")**2" << endl;
        //fout << "p" << i << "(x, y) = " << a << "*(x - " << ux[i] << ")**2 + (" << b << " + " << c << ")*(x - " << ux[i] << ")*(y - " << uy[i] << ") + " << d << "*(y - " << uy[i] << ")**2 - 4" << endl; 
        // f(x,y) = a*(x - ux)^2 + (b + c)*(x - ux)(y - uy) + d*(y - uy)^2 
    }
    fout.close();
}

double Em_alg::probability_to_j(const vector <vector <double>> &cov_mat, const vector <double> &x, const vector <double> &y, const vector <double> &ux, const vector <double> &uy, const int &i, const int &j)
{
    double a, b, c, d, x1, x2;
    //cout << gx << " " << gy << endl;
    double detE = det(cov_mat);

    //cout << detE << endl;
    //getchar();
    a = cov_mat[1][1]/detE;
    b = -cov_mat[0][1]/detE;
    c = -cov_mat[1][0]/detE;
    d = cov_mat[0][0]/detE;
    x1 = x[i] - ux[j];
    x2 = y[i] - uy[j];
    //cout << a << " " << b << " " << c << " " << d << " " << x1 << " " << x2 << endl;
    //getchar();
    double pi = acos(-1);
    double c1 = sqrt(2*pi*detE);
    double c2 = -(a*x1*x1 + x1*x2*c + x1*x2*b + x2*x2*d)/2;

    return (1/c1)*exp(c2);
}

vector <Cluster> Em_alg::turn_EM(int k, Field &field)
{
    // нач состояние кластеров - центры первые к точек, P(a) = 1/k, мат ожидания это эти точки
    // нам нужны векторы x, y, P(a1),...,P(ak), - вероятности и ai - центры с координатами (ua1, ua2) - мат ожидания
    // формула для пересчитывания мат ожидания - u = (a, x1)/(SUM(ai/ai));

    clock_t time;
    ios::sync_with_stdio(0);
    cin.tie(0);

    vector <double> probability(k);
    vector <vector <double>> a(k);
    vector <vector <double>> prev(k);
    vector <vector <vector <double>>> covm(k);
    vector <double> ux(k);
    vector <double> uy(k);

    int N = field.size();
    vector <double> x(N);
    vector <double> y(N);

    vector <Cluster> clusters(k);
    vector <Point> &points = field.get_points_reference();

    for (int i = 0; i < k; i++)
    {
        probability[i] = (double)1/k;
        a[i].resize(N);
        prev[i].resize(N);
        clusters[i].reserve(N);
        ux[i] = points[i].getx();
        uy[i] = points[i].gety();
    }
    //cout << "Init" << endl;

    for (int i = 0; i < k; i++)
    {
        covm[i].resize(2);
        for (int j = 0; j < 2; j++)
        {
            covm[i][j].resize(2);
        }
    }
   // cout << "Mat init" << endl;

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < N; j++)
        {
             prev[i][j] = 0;
        }
    }

    for (int i = 0; i < N; i++)
    {
        x[i] = points[i].getx();
        y[i] = points[i].gety();
    }
   // cout << "Point init " << endl;

    for (int j = 0; j < k; j++)
    {
        double meanx = 0;
        double meany = 0;
        for (int i = 0; i < N; i++)
        {
           // int m = rand()%k;
            int m = j;
            meanx += (x[i] - ux[m])*(x[i] - ux[m]);
            meany += (y[i] - uy[m])*(y[i] - uy[m]);
            //meanx += fabs(x[i] - ux[j]);
            //meany += fabs(y[i] - uy[j]);
        }
        meanx /= N;
        meany /= N;
        covm[j][0][0] = meanx;
        covm[j][1][1] = meany;
        covm[j][1][0] = 0;
        covm[j][0][1] = 0;
    }

    cout << "gx cov u init " << endl;

    time = clock();
    while(1)
    {
        for (int i = 0; i < k; i++)
            prev[i] = a[i];
        for (int j = 0; j < k; j++)
        {
            for (int i = 0; i < N; i++)
            {
                double sum = 0;
                for (int m = 0; m < k; m++)
                    sum += probability[m]*probability_to_j(covm[m], x, y, ux, uy, i, m);
                if (sum < 1e-25) break;
                a[j][i] = probability_to_j(covm[j], x, y, ux, uy, i, j)*probability[j]/sum;
            }
        }

        for (int j = 0; j < k; j++)
            probability[j] = P(a[j]);

        for (int j = 0; j < k; j++)
        {
            ux[j] = 0;
            uy[j] = 0;
            for (int i = 0; i < N; i++)
            {
                ux[j] += a[j][i]*x[i];
                uy[j] += a[j][i]*y[i];
            }
            if (probability[j] < 1e-25) break;
            ux[j] /= probability[j];
            uy[j] /= probability[j];
            ux[j] /= N;
            uy[j] /= N;
        }

        for (int j = 0; j < k; j++)
        {
            covm[j][0][0] = cov_matrix_xy(x, x, ux, ux, a[j], probability[j], j);
            covm[j][0][1] = cov_matrix_xy(x, y, ux, uy, a[j], probability[j], j);
            covm[j][1][1] = cov_matrix_xy(y, y, uy, uy, a[j], probability[j], j);
            covm[j][1][0] = covm[j][0][1];
        }

        bool flag = 0;

        //cout << 1 << endl;

        for (int i = 0; i < k; i++)
        {
            //cout << "norma " << norma(prev[i], a[i]) << endl;
            if (norma(prev[i], a[i]) > EPSILON)
            {
                flag = 1;
                continue;
            }
        }
        if (flag == 0) break;
    }
    cout << "EM algorithm has perfectly done" << endl;
    time = clock() - time;
    cout << "It has been taken " << (double)time/CLOCKS_PER_SEC << " seconds" << endl;

    for (int i = 0; i < N; i++)
    {
        double max = 0;
        int indm = 0;
        for (int j = 0; j < k; j++)
        {
            if (a[j][i] >= max)
            {
                max = a[j][i];
                indm = j;
            }
        }
        clusters[indm].add_p(i);
   }

   printEllipsesForGNU(covm, ux, uy, k);

   vector <double> ().swap(probability);
   vector <double> ().swap(ux);
   vector <double> ().swap(uy);
   vector <double> ().swap(x);
   vector <double> ().swap(y);
   vector <vector <double>> ().swap(prev);
   vector <vector <double>> ().swap(a);
   vector <vector <vector <double>>> ().swap(covm);

   return clusters;
}

double Em_alg::P(const vector <double> &a)
{
    int n = static_cast<int> (a.size());
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
    }
    sum /= n;
    return sum;
}