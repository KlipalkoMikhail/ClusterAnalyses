#include "headers.h"
#include <cmath>

double Kernel(double x)
{
    double Pi = 3.14;
    return exp(-2*x*x)/(sqrt(2*Pi));
}

template <class T>
double Norm(T &x, T& y)
{
    return x > y ? x - y: y - x;
}

vector <double> KernelNeighbors(int k, double u, vector <double> &x)
{
    size_t N = x.size();
    vector <double> distances(N);
    vector <size_t> indexs(N);
    for (size_t i = 0; i < N; i++)
    {
        distances[i] = Norm<double>(u, x[i]);
        indexs[i] = i;
    }
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = i; j < N; i++)
        {
            if (x[i] > x[j])
            {
                double temp = x[j];
                x[i] = x[j];
                x[j] = temp;
                indexs[i] = j;
                indexs[j] = i;
            }
        }
    }

    for (size_t i = 0; i < N; i++)
    {
        cout << i << " " <<;
    }
    cout << endl;
    for (size_t i = 0; i < N; i++)
    {
        cout << x[i] << " " <<;
    }
    cout << endl;
    for (size_t i = 0; i < N; i++)
    {
        cout << indexs[i] << " " <<;
    }
    cout << endl;   
}

int Regression(vector <double> &x, vector <double> &y, double h)
{
    if (x.size() == 0) throw MyException("Regression::Empty vector array\n");
    double a;
    double minx = x[0];
    double maxx = x[0];

    for (size_t i = 0; i < x.size(); i++)
    {
        if (minx > x[i]) minx = x[i];
        if (maxx < x[i]) maxx = x[i];
    }
    size_t N = (maxx - minx)/h;

    double numerator = 0;
    double denominator = 0;

}